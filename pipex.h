/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:23:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 20:49:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		fd[2];
	int		pid;
}			t_cmd;

typedef struct s_pipex
{
	int		in_file;
	int		out_file;
	int		here_doc_file;
	bool	here_doc;
	char	**argv;
	char	**envp;
	int		exit_status;
	t_cmd	*cmds;
	size_t	cmd_count;
}			t_pipex;

char		*get_next_line(int fd);

//  INIT
void		init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);

//  STRS
int			count_words(char *str, char sep);
char		*strjoin_three(char *s1, char *s2, char *s3);
void		free_until_null(char ***str_v);

//  CMDS
void		free_cmds(t_pipex *pipex);
char		*find_path(char *cmd, char **envp);
char		**populate_args(t_cmd *cmd, char **args, size_t wc);
t_cmd		*build_command(char *cmd_str, char **envp);
int			parse_cmds(t_pipex *pipex);

// PIPES
void		connect_in(t_pipex *pipex, t_cmd *cmd, bool first);
void		connect_out(t_pipex *pipex, t_cmd *cmd, bool last);
void		open_pipes(t_pipex *pipex);
void		close_fds(t_pipex *pipex);
void		wait_pids(t_pipex *pipex);
void		exec(t_pipex *pipex, t_cmd *cmd, size_t index);
void		pipe_exec_them(t_pipex *pipex);

# ifdef BONUS
// HERE_DOC
void		here_doc_get(int fd[2], const char *limiter);
void		here_doc(t_pipex *pipex, char *limiter);
# endif
//  CLEANUP
void		error_exit(t_pipex *pipex, const char *errorstr);
#endif