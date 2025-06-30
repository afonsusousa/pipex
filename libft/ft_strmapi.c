/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:39:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/15 21:01:40 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	ret = ft_strdup(s);
	if (!ret)
		return (NULL);
	while (ret[i])
	{
		ret[i] = (*f)(i, ret[i]);
		i++;
	}
	return (ret);
}
