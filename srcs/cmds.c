/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:18:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 20:08:35 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_cmds(t_pipex *pipex)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	while (i < pipex->cmd_count)
	{
		cmd = build_command(pipex->argv[i + 2 + pipex->here_doc], pipex->envp);
		if (!cmd)
			error_exit(pipex, NULL);
		pipex->cmds[i] = *cmd;
		free(cmd);
		i++;
	}
	return (1);
}

char	*find_path(char *cmd, char **envp)
{
	size_t	i;
	char	**split_path;
	char	*try;

	i = 0;
	while (*envp)
		if (!ft_strncmp("PATH=", *envp++, 5))
			break ;
	if (!*envp)
		return (NULL);
	split_path = ft_split(*envp + 5, ':');
	if (!split_path)
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
	return (free_until_null(&split_path), ft_strdup(cmd));
}

char	**populate_args(t_cmd *cmd, char **args, size_t wc)
{
	size_t	i;

	i = 0;
	if (wc > 0)
	{
		cmd->args = malloc((wc + 1) * sizeof(char *));
		if (!cmd->args)
			return (NULL);
		while (i < wc)
		{
			cmd->args[i] = ft_strdup(args[i]);
			if (!cmd->args[i])
				return (NULL);
			i++;
		}
		cmd->args[i] = NULL;
	}
	return (cmd->args);
}

t_cmd	*build_command(char *cmd_str, char **envp)
{
	int		wc;
	char	**cmd_str_split;
	t_cmd	*ret;

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
