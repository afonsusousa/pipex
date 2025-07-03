/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:22:33 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 19:49:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipex *pipex, const char *errorstr)
{
	free_cmds(pipex);
	perror(errorstr);
	if (pipex->in_file != -1)
		close(pipex->in_file);
	if (pipex->out_file != -1)
		close(pipex->out_file);
	exit(pipex->exit_status);
}

void	close_fds(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (close(pipex->cmds[i].fd[READ_END]) == -1)
			error_exit(pipex, NULL);
		if (close(pipex->cmds[i++].fd[WRITE_END]) == -1)
			error_exit(pipex, NULL);
	}
}

void	wait_pids(t_pipex *pipex)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (waitpid(pipex->cmds[i].pid, &status, 0) == -1)
			error_exit(pipex, "waitpid");
		if (i == pipex->cmd_count - 1)
		{
			if (WIFEXITED(status))
				pipex->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				pipex->exit_status = 128 + WTERMSIG(status);
			else
				pipex->exit_status = 1;
		}
		i++;
	}
}