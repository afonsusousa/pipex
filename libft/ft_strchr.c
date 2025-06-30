/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:00:41 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 18:08:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	if (!(char)c)
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
