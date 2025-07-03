/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:19:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 19:55:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	ft_memset(&pipex, 0, sizeof(pipex));
	if (argc < 5)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		pipex.here_doc = false;
		pipex.in_file = open(argv[1], O_RDONLY);
		pipex.out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	else
	{
		here_doc(&pipex, argv[2]);
		pipex.here_doc = true;
		pipex.out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
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