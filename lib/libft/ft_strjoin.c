/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:36:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:31 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ret = (void *)ft_calloc(len, 1);
	if (!ret)
		return (NULL);
	ft_strlcat(ret, s1, len);
	ft_strlcat(ret, s2, len);
	return (ret);
}

/*
#include <stdio.h>
int main()
{
	char dest[50] = "Hello, ";
	char *src = "World!";
	printf("%s\n", ft_strjoin(dest, src));
}
*/
