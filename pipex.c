/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:13:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/02 20:57:44 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "libft/libft.h" 


# define READ_END 0
# define WRITE_END 1

char    *get_next_line(int fd);
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
    int     here_doc_file;
    bool    here_doc;
    char    **argv;
    char    **envp;
    int     exit_status;
    t_cmd   *cmds;
    size_t  cmd_count;
} t_pipex;

void    free_until_null(char ***str_v)
{
    size_t  i;

    i = 0;
    if (!*str_v)
        return ;
    while ((*str_v)[i])
        free((*str_v)[i++]);
    free(*str_v);
    *str_v = NULL;
}

void    free_cmds(t_pipex *pipex)
{
    size_t  i;

    i = 0;
    while (i < pipex->cmd_count)
    {
        free_until_null(&pipex->cmds[i].args);
        if (pipex->cmds[i].path)
            free(pipex->cmds[i].path);
        i++;
    }
    free(pipex->cmds);
}

void    error_exit(t_pipex *pipex, const char *errorstr)
{
    free_cmds(pipex);
    perror(errorstr);
    if (pipex->in_file != -1)
        close(pipex->in_file);
    if (pipex->out_file != -1)
        close(pipex->out_file);
    exit(pipex->exit_status);
}

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
    size_t     i;
    char **split_path;
    char *try;

    i = 0;
    while (*envp)
    {
        if (!ft_strncmp("PATH=", *envp, 5))
            break;
        envp++;
    }
    if (!*envp)
        return (NULL);
    split_path = ft_split(*envp + 5, ':');
    if(!split_path)
        return (NULL);
    while (split_path[i])
    {
        try = strjoin_three(split_path[i++], "/", cmd);
        if (!try)
            return (free_until_null(&split_path), NULL);
        if (access(try, X_OK) == 0)
            return (free_until_null(&split_path), try);
        free(try);
    }
    return (free_until_null(&split_path), NULL);
}

char    **populate_args(t_cmd *cmd, char **args, size_t wc)
{
    size_t i;

    i = 0;
    if (wc > 0)
    {
        cmd->args = malloc((wc + 1) * sizeof(char *));
        if (!cmd->args)
           return (NULL);
        while (i < wc)
        {
            cmd->args[i] = ft_strdup(args[i]);
            if(!cmd->args[i])
               return (NULL);
            i++;
        }
        cmd->args[i] = NULL;
    }
    return (cmd->args);
}
t_cmd   *build_command(char *cmd_str, char **envp)
{
    int wc;
    char **cmd_str_split;
    t_cmd *ret;

    wc = count_words(cmd_str, ' ');
    cmd_str_split = ft_split(cmd_str, ' ');
    if (!cmd_str_split)
        return (NULL);
    ret = calloc(1, sizeof(t_cmd));
    if (!ret)
        return (NULL);
    if (wc)
        ret->path = find_path(cmd_str_split[0], envp);
    if (!ret->path)
        return (free(ret), free_until_null(&cmd_str_split), NULL);
    if (!populate_args(ret, cmd_str_split, wc))
        return (free(ret), free_until_null(&cmd_str_split), NULL);
    return (free_until_null(&cmd_str_split), ret);
}

void close_fds(t_pipex *pipex)
{
    size_t  i;
    
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (close(pipex->cmds[i].fd[READ_END]) == -1)
            error_exit(pipex, NULL);
        if (close(pipex->cmds[i++].fd[WRITE_END]) == -1)
            error_exit(pipex, NULL);
    }
}

void    connect_in(t_pipex *pipex, t_cmd *cmd, bool first)
{
    if (first)
    {
        if (dup2(pipex->in_file, STDIN_FILENO) == -1)
        {
            pipex->exit_status = 1;
            error_exit(pipex, pipex->argv[1]);
        }
    }
    else
    {
        if (dup2((cmd - 1)->fd[READ_END], STDIN_FILENO) == -1)
            error_exit(pipex, NULL);
    }
}
void    connect_out(t_pipex *pipex, t_cmd *cmd, bool last)
{
    if (last)
    {
        if (dup2(pipex->out_file, STDOUT_FILENO) == -1)
        {
            pipex->exit_status = 1;
            error_exit(pipex, NULL);
        }
    }
    else
    {
        if (dup2(cmd->fd[WRITE_END], STDOUT_FILENO) == -1)
            error_exit(pipex, NULL);
    }
}

void    open_pipes(t_pipex *pipex)
{
    size_t  i;

    i = 0;
    while (i < pipex->cmd_count - 1)
        if(pipe(pipex->cmds[i++].fd) == -1)
            error_exit(pipex, NULL);
}

void    wait_pids(t_pipex *pipex)
{
    size_t  i;
    int     status;
    
    i = 0;
    while (i < pipex->cmd_count)
    {
        waitpid(pipex->cmds[i].pid, &status, 0);
        if (i == pipex->cmd_count - 1)
        {
            if (WIFEXITED(status))
			    pipex->exit_status = WEXITSTATUS(status);
		    else
			    pipex->exit_status = 1;
        }
        i++;
    }
}

void    exec(t_pipex *pipex, t_cmd *cmd, size_t index)
{
    connect_in(pipex, cmd, (index == 0));
    connect_out(pipex, cmd, (index == pipex->cmd_count - 1));
    close_fds(pipex);
    if (execve(cmd->path, cmd->args, pipex->envp) == -1)
    {
        pipex->exit_status = 127;
        error_exit(pipex, NULL);
    }
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
        if(cmd->pid == -1)
            error_exit(pipex, NULL);
        if (cmd->pid == 0)
            exec(pipex, cmd, i);
        i++;
    }
    close_fds(pipex);
    wait_pids(pipex);
}

void here_doc_get(int fd[2], const char *limiter)
{
    char *line;
    
    close(fd[READ_END]);
    line = get_next_line(0);
    while (line && ft_strncmp(line, limiter, ft_strlen(limiter) != 0))
    {
        ft_putstr_fd(line, fd[WRITE_END]);
        free(line);
        line = get_next_line(0);
    }
    if (line)
    free(line);
    exit(0);
}

void here_doc(t_pipex *pipex, char *limiter)
{
    int     fd[2];
    pid_t pid;
    
    if(pipe(fd) == -1)
        error_exit(pipex, NULL);
    pid = fork();
    if (pid == -1)
        error_exit(pipex, NULL);
    if (pid == 0)
        here_doc_get(fd, limiter);
    else
    {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO);
        wait(NULL);
    }
}

int    parse_cmds(t_pipex *pipex)
{
    size_t     i;
    t_cmd   *cmd;
    
    i = 0;
    while (i < pipex->cmd_count )
    {
        cmd = build_command(pipex->argv[i + 2 + pipex->here_doc], pipex->envp);
        if (!cmd)
        {
            if (i == pipex->cmd_count - 1)
                pipex->exit_status = 127;
            error_exit(pipex, pipex->argv[i + 2 + pipex->here_doc]);
        }
        pipex->cmds[i] = *cmd;
        free(cmd);
        i++;
    }
    return (1);
}
int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    ft_memset(&pipex, 0, sizeof(pipex));
    if (argc < 5)
    return (1);
    if (ft_strncmp(argv[1], "here_doc", 9) != 0)
    {
        pipex.here_doc = false;
        pipex.in_file = open(argv[1], O_RDONLY);
{}        pipex.out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    else
    {
        here_doc(&pipex, argv[2]);
        pipex.here_doc = true;
        pipex.out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    pipex.cmd_count = argc - 3 - pipex.here_doc;
    pipex.cmds = ft_calloc(pipex.cmd_count, sizeof(t_cmd));
    pipex.argv = argv;
    pipex.envp = envp;
    parse_cmds(&pipex);
    pipe_exec_them(&pipex);
    free_cmds(&pipex);
    close(pipex.in_file);
    close(pipex.out_file);
    return (pipex.exit_status);
}