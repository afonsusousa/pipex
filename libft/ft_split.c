/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:44:36 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/15 16:12:03 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_words(const char *str, const char sep)
{
	size_t	i;
	int		words;

	i = 0;
	words = (str[0] != sep) && (str[0] != 0);
	while (str[i])
	{
		if (str[i] == sep && str[i + 1] != sep && str[i + 1])
			words++;
		i++;
	}
	return (words);
}

static void	ft_free(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
		free(ret[i++]);
	free(ret);
}

static size_t	ft_inject_word(char **ret, const char *word, size_t *i, char c)
{
	size_t	word_len;

	word_len = 0;
	while (word[word_len] != c && word[word_len])
		word_len++;
	*ret = ft_substr(word, 0, word_len);
	if (!(*ret))
		return (0);
	*i += word_len;
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	word;
	char	**ret;

	i = 0;
	word = -1;
	if (!s)
		return (0);
	ret = (char **)ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			if (!ft_inject_word(&ret[++word], &s[i], &i, c))
				return (ft_free(ret), NULL);
		}
		else
			i++;
	}
	return (ret);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
	//char **split = ft_split("hello asd asd as d", ' '); 
	//for(int i = 0; i < ft_count_words("hello!", ' '); i++)
	//	printf("letra qualquer %d %s\n", i, split[i]);
	char **split = ft_split(argv[1], argv[2][0]);
	for(int i = 0; i < ft_count_words(argv[1], argv[2][0]); i++)
		printf("%s\n", split[i]);
}
*/
