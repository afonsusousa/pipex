/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:19:08 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/04 23:01:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	connect_in(t_pipex *pipex, t_cmd *cmd, bool first)
{
	if (first)
	{
		if (dup2(pipex->in_file, STDIN_FILENO) == -1)
		{
			pipex->exit_status = 1;
			close_fds(pipex);
			error_exit(pipex, pipex->argv[1]);
		}
	}
	else
	{
		if (dup2((cmd - 1)->fd[READ_END], STDIN_FILENO) == -1)
			error_exit(pipex, NULL);
	}
}

void	connect_out(t_pipex *pipex, t_cmd *cmd, bool last)
{
	if (last)
	{
		if (dup2(pipex->out_file, STDOUT_FILENO) == -1)
		{
			pipex->exit_status = 1;
			close_fds(pipex);
			error_exit(pipex, pipex->argv[pipex->cmd_count + 2]);
		}
	}
	else
	{
		if (dup2(cmd->fd[WRITE_END], STDOUT_FILENO) == -1)
			error_exit(pipex, NULL);
	}
}

void	open_pipes(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
		if (pipe(pipex->cmds[i++].fd) == -1)
			error_exit(pipex, NULL);
}

void	exec(t_pipex *pipex, t_cmd *cmd, size_t index)
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

void	pipe_exec_them(t_pipex *pipex)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	open_pipes(pipex);
	while (i < pipex->cmd_count)
	{
		cmd = &pipex->cmds[i];
		cmd->pid = fork();
		if (cmd->pid == -1)
			error_exit(pipex, NULL);
		if (cmd->pid == 0)
			exec(pipex, cmd, i);
		i++;
	}
	close_fds(pipex);
	wait_pids(pipex);
}
