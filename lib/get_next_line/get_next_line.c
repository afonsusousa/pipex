/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:57:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/07 00:45:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	ft_foundnew(t_list *lst, int fd)
{
	int	i;

	i = -1;
	lst = ft_lstlast(lst, fd);
	while (lst && lst->str[++i])
		if (lst->str[i] == '\n')
			return (1);
	return (0);
}

void	get_list(t_list **dest, int fd)
{
	int		rd;
	char	*buffer;

	while (!ft_foundnew(*dest, fd))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (ft_freelist(dest, fd));
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
		{
			free(buffer);
			if (rd < 0)
				ft_freelist(dest, fd);
			return ;
		}
		buffer[rd] = '\0';
		ft_add_back(dest, buffer, fd);
	}
}

char	*serve_line(t_list *lst, int fd)
{
	int		linelen;
	t_list	*iter;
	char	*ret;

	linelen = 0;
	iter = lst;
	if (!iter)
		return (NULL);
	while (iter)
	{
		if (iter->fd == fd)
			linelen += ft_newlen(iter->str);
		iter = iter->next;
	}
	ret = (char *)malloc(linelen + 2);
	if (!ret)
		return (NULL);
	return (ft_strcnpy(lst, ret, fd));
}

void	clean_list(t_list **lst, int fd)
{
	int		i;
	int		j;
	char	*buffer;
	t_list	*last;

	last = ft_lstlast(*lst, fd);
	if (!last)
		return ;
	i = ft_newlen(last->str);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_freelist(lst, fd));
	j = 0;
	while (last->str[i] && last->str[++i])
		buffer[j++] = last->str[i];
	buffer[j] = '\0';
	ft_freelist(lst, fd);
	ft_add_back(lst, buffer, fd);
}

char	*get_next_line(int fd)
{
	static t_list	*line = NULL;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	get_list(&line, fd);
	if (!line)
		return (NULL);
	ret = serve_line(line, fd);
	if (!ret)
		return (ft_freelist(&line, fd), NULL);
	clean_list(&line, fd);
	return (ret);
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	int	file = open(argv[1], O_RDONLY);
// 	char *line;
// 	while(line = get_next_line(file))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}

// 	close (file);
// 	file = open(argv[1], O_RDONLY);
// 	while(line = get_next_line(file))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	free(line);
// 	close(file);
// }
