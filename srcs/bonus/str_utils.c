/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:19:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/03 20:10:24 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_words(char *str, char sep)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*str)
	{
		if (!in_word && *str != sep)
		{
			in_word = true;
			count++;
		}
		else if (*str == sep)
			in_word = false;
		str++;
	}
	return (count);
}

char	*strjoin_three(char *s1, char *s2, char *s3)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!ret)
		return (NULL);
	if (!s1 || !s2 || !s3)
		return (NULL);
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	while (*s3)
		ret[i++] = *s3++;
	ret[i] = 0;
	return (ret);
}
