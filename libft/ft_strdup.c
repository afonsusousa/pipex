/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:37:30 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/10 19:53:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*t;
	char	*r;
	size_t	len;

	len = ft_strlen((char *)s);
	t = (char *)malloc(len + 1);
	if (!t)
		return (NULL);
	r = t;
	while ((size_t)(t - r) < len)
		*t++ = *s++;
	*t = 0;
	return (r);
}
