/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:57:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/07 00:47:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}	t_list;

char	*ft_strcnpy(t_list *lst, char *dest, int fd);
int		ft_newlen(char *str);
t_list	*ft_lstlast(t_list *lst, int fd);
void	ft_add_back(t_list **lst, char *str, int fd);
void	ft_freelist(t_list **lst, int fd);
int		ft_foundnew(t_list *lst, int fd);
void	get_list(t_list **dest, int fd);
char	*serve_line(t_list *lst, int fd);
void	clean_list(t_list **lst, int fd);
char	*get_next_line(int fd);

#endif
