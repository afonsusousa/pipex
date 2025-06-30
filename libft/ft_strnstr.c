/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:06:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/10 20:42:42 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;

	b = (char *)big;
	if (!len && !big)
		return (NULL);
	if (!(*little))
		return ((char *)big);
	while (*b && (size_t)(b - big) < len)
	{
		i = 0;
		while (b[i] == little[i] && b[i] && (b - big) + i < len)
		{
			if (little[i + 1] == 0)
				return (b);
			i++;
		}
		b++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int main()
{
	const char *str1 = NULL;
	const char *str2 = "teu";
	printf("%s\n", strnstr(str1, str2, 0));
	printf("%s\n", ft_strnstr(str1, str2, 0));
}
*/
