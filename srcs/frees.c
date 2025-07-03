/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:18:58 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 19:20:46 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_until_null(char ***str_v)
{
	size_t	i;

	i = 0;
	if (!*str_v)
		return ;
	while ((*str_v)[i])
		free((*str_v)[i++]);
	free(*str_v);
	*str_v = NULL;
}

void	free_cmds(t_pipex *pipex)
{
	size_t	i;

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