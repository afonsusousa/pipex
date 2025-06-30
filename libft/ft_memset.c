/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:36:47 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/04 15:39:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*(((unsigned char *) s) + i++) = c;
	return (s);
}

/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *arr = malloc(5);
	ft_memset(arr, 97, 5);
	for(int i = 0; i < 5; i++)
			printf("%c\n", arr[i]);
	free(arr);
}
*/
