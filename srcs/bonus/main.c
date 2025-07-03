/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:19:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 21:01:18 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (1);
	ft_memset(&pipex, 0, sizeof(pipex));
	init_pipex(&pipex, argc, argv, envp);
	parse_cmds(&pipex);
	pipe_exec_them(&pipex);
	free_cmds(&pipex);
	if (pipex.in_file != -1)
		close(pipex.in_file);
	if (pipex.out_file != -1)
		close(pipex.out_file);
	return (pipex.exit_status);
}
