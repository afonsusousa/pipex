/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:53:06 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/15 00:51:45 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(const char c, const char *set)
{
	if (!c)
		return (1);
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s1 || !set)
		return (0);
	start = -1;
	end = ft_strlen((char *)s1) + 1;
	while (ft_inset(s1[++start], set))
		;
	while (ft_inset(s1[--end], set))
		;
	ret = ft_substr(s1, start, end - start + 1);
	return (ret);
}

/*
#include <stdio.h>
int main()
{
	char *a = "           ouro            ";
	char *set = " ";
	printf("%s", ft_strtrim(a, set));
}
*/
