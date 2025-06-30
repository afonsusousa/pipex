/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:44:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen((char *)src);
	if (!dest && !size)
		return (src_len);
	dest_len = ft_strlen((char *)dest);
	if (size <= dest_len)
		return (src_len + size);
	i = dest_len;
	j = 0;
	while (src[j] && i + 1 < size)
		dest[i++] = src[j++];
	dest[i] = 0;
	return (src_len + dest_len);
}
