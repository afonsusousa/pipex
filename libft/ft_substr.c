/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:01:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 18:14:55 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	src_len;

	if (!s)
		return (ft_strdup(""));
	src_len = (unsigned int )ft_strlen((char *)s);
	if (start >= src_len)
		return (ft_strdup(""));
	if (start + len > src_len)
		len = src_len - start;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, (char *)&s[start], len + 1);
	return (ret);
}
