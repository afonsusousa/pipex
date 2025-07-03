/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:19:04 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 20:08:17 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_get(int fd[2], const char *limiter)
{
	char	*line;

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

void	here_doc(t_pipex *pipex, char *limiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
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
