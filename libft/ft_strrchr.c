/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:28:23 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 18:09:42 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ct;

	i = ft_strlen(s);
	ct = (char) c;
	if (ct == 0)
		return ((char *) &s[i]);
	while (--i >= 0)
		if (s[i] == ct)
			return ((char *)&s[i]);
	return (NULL);
}
