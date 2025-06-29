/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:13:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/29 20:26:25 by amagno-r         ###   ########.fr       */
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
    char    **envp;
    int     fd[2];
    int     pid;
}   t_cmd;

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
        if (!access(try, X_OK))
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
    cmd_str_split = ft_split(cmd_str, ' ');
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
        ret->args = malloc((wc + 1) * sizeof(char *));
        while (++i < wc)
            ret->args[i] = ft_strdup(cmd_str_split[i]);
        ret->args[i] = NULL;    
    }
    ret->envp = envp;
    free(cmd_str_split);
    return (ret);
}

void close_fds(t_cmd *cmds, size_t n)
{
    size_t  i;
    
    i = 0;
    while (i < n - 1)
    {
        close(cmds[i].fd[READ_END]);
        close(cmds[i].fd[WRITE_END]);
        i++;
    }
}

void    open_pipes(t_cmd *cmds, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n - 1)
    {
        pipe(cmds[i].fd);
        i++;
    }
}

void    wait_pids(t_cmd *cmds, size_t n)
{
    size_t  i;
    
    i = 0;
    while (i < n)
    {
        waitpid(cmds[i].pid, NULL, 0);
        i++;
    }
}
void    pipe_them(int in_file, int outfile, t_cmd *cmds, size_t n)
{
    size_t i = 0;
    
    i = 0;
    open_pipes(cmds, n);
    while (i < n)
    {
        cmds[i].pid = fork();
        if (cmds[i].pid == 0)
        {
            if (i == 0)
                dup2(in_file, STDIN_FILENO);
            else
                dup2(cmds[i-1].fd[READ_END], STDIN_FILENO);
            if (i == n - 1)
                dup2(outfile, STDOUT_FILENO);
            else
                dup2(cmds[i].fd[WRITE_END], STDOUT_FILENO);
            close_fds(cmds, n);
            execve(cmds[i].path, cmds[i].args, cmds[i].envp);
            exit(1);
        }
        i++;
    }
    close_fds(cmds, n);
    wait_pids(cmds, n);
}

int main(int argc, char **argv, char **envp)
{
    int i;
    int in_file;
    int out_file;
    t_cmd *cmds;
    t_cmd *cmd;

    if (argc < 5)
        return (1);
    i = 0;

    in_file = open(argv[1], O_RDONLY);
    out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    cmds = ft_calloc(argc - 3, sizeof(t_cmd));
    while (i < argc - 3)
    {
        cmd = build_command(argv[i + 2], envp);
        if (!cmd)
        {
            while(i--)
                free(&cmds[i]);
            return (1);
        }
        cmds[i] = *cmd;
        free(cmd);
        i++;
    }
    pipe_them(in_file, out_file, cmds, argc - 3);
    close(in_file);
    close(out_file);
    return (0);
}