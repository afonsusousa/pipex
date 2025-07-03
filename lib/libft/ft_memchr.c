/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:40:51 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 18:18:25 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t;

	if (!n)
		return (0);
	t = (unsigned char *)s;
	while (--n && *t != (unsigned char) c)
		t++;
	if (*t == (unsigned char)c)
		return (t);
	return (NULL);
}
