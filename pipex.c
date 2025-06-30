/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:13:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/30 19:53:47 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "../libft/libft.h" 

# define READ_END 0
# define WRITE_END 1

typedef struct s_cmd
{
    char    *path;
    char    **args;
    int     fd[2];
    int     pid;
}   t_cmd;

typedef struct s_pipex
{
    int     in_file;
    int     out_file;
    bool    here_doc;
    char    **argv;
    char    **envp;
    t_cmd   *cmds;
    size_t  cmd_count;
} t_pipex;

int count_words(char *str, char sep)
{
    int count;
    bool in_word;
    
    count = 0;
    in_word = false;
    while (*str)
    {
        if(!in_word && *str != sep)
        {
            in_word = true;
            count++;
        }
        else if (*str == sep)
            in_word = false;
        str++;
    }
    return (count);
}

char    *strjoin_three(char *s1, char *s2, char *s3)
{
    int     i;
    char    *ret;
    
    i = 0;
    ret = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
    if (!ret)
        return (NULL);
    if (!s1 || !s2 || !s3)
        return (NULL);
    while (*s1)
        ret[i++] = *s1++;
    while (*s2)
        ret[i++] = *s2++;
    while (*s3)
        ret[i++] = *s3++;
    ret[i] = 0;
    return (ret);
}

char *find_path(char *cmd, char **envp)
{
    char **split_path;
    char *try;
    while (*envp)
    {
        if (!ft_strncmp("PATH=", *envp, 5))
            break;
        envp++;
    }
    if (!*envp)
        return (NULL);
    split_path = ft_split(*envp + 5, ':');
    while (*split_path)
    {
        try = strjoin_three(*split_path++, "/", cmd);
        if (!try)
            return (free(split_path), NULL);
        if (access(try, X_OK) == 0)
            return (try);
        free(try);
    }
    return (free(split_path), NULL);
}

t_cmd   *build_command(char *cmd_str, char **envp)
{
    int wc;
    int i;
    char **cmd_str_split;
    t_cmd *ret;

    wc = count_words(cmd_str, ' ');
    cmd_str_split = ft_split(cmd_str, ' '); //needs malloc check
    ret = calloc(1, sizeof(t_cmd));
    if (!ret)
        return (NULL);
    if (wc)
        ret->path = find_path(cmd_str_split[0], envp);
    if (!ret->path)
        return (free(ret), free(cmd_str_split), NULL);
    i = -1;
    if (wc > 0)
    {
        ret->args = malloc((wc + 1) * sizeof(char *)); //needs malloc check
        while (++i < wc)
            ret->args[i] = ft_strdup(cmd_str_split[i]); //needs malloc check
        ret->args[i] = NULL;    
    }
    return (free(cmd_str_split), ret);
}

void close_fds(t_pipex *pipex)
{
    size_t  i;
    
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        close(pipex->cmds[i].fd[READ_END]);
        close(pipex->cmds[i++].fd[WRITE_END]);
    }
}

void    open_pipes(t_pipex *pipex)
{
    size_t  i;

    i = 0;
    while (i < pipex->cmd_count)
        pipe(pipex->cmds[i++].fd);
}

void    wait_pids(t_pipex *pipex)
{
    size_t  i;
    
    i = 0;
    while (i < pipex->cmd_count)
        waitpid(pipex->cmds[i++].pid, NULL, 0);
}

void    connect(t_pipex *pipex, t_cmd *cmd, bool first, bool last)
{
    if (first)
        dup2(pipex->in_file, STDIN_FILENO);
    else
        dup2((cmd - 1)->fd[READ_END], STDIN_FILENO);
    if (last)
        dup2(pipex->out_file, STDOUT_FILENO);
    else
        dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
}

void    exec(t_pipex *pipex, t_cmd *cmd, size_t index)
{
    connect(pipex, cmd, (index == 0), (index == (pipex->cmd_count - 1)));
    close_fds(pipex);
    execve(pipex->cmds[index].path, 
            pipex->cmds[index].args, 
            pipex->envp);
    exit(1);
}
void    pipe_exec_them(t_pipex *pipex)
{
    size_t  i;
    t_cmd   *cmd;
    
    i = 0;
    open_pipes(pipex);
    while (i < pipex->cmd_count)
    {
        cmd = &pipex->cmds[i];
        cmd->pid = fork();
        if (pipex->cmds[i].pid == 0)
            exec(pipex, cmd, i);
        i++;
    }
    close_fds(pipex);
    wait_pids(pipex);
}

int    parse_cmds(t_pipex *pipex)
{
    int     i;
    t_cmd   *cmd;
    
    i = 0;
    while (i < pipex->cmd_count)
    {
        cmd = build_command(pipex->argv[i + 2], pipex->envp);
        if (!cmd)
        {
            while(i--)
                free(&pipex->cmds[i]);
            return (0);
        }
        pipex->cmds[i] = *cmd;
        free(cmd);
        i++;
    }
    return (1);
}
int main(int argc, char **argv, char **envp)
{
    int     i;
    t_pipex pipex;
    ft_memset(&pipex, 0, sizeof(pipex));
    if (argc < 5)
        return (1);
    i = 0;
    pipex.in_file = open(argv[1], O_RDONLY);
    pipex.out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pipex.cmd_count = argc - 3;
    pipex.cmds = ft_calloc(pipex.cmd_count, sizeof(t_cmd));
    pipex.argv = argv;
    pipex.envp = envp;
    parse_cmds(&pipex);
    pipe_exec_them(&pipex);
    close(pipex.in_file);
    close(pipex.out_file);
    return (0);
}