/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 01:32:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/14 18:00:53 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t size)
{
	size_t	total;
	void	*ret;

	if (!n || !size)
		return (malloc(0));
	total = n * size;
	ret = malloc(total);
	if (!ret)
		return (NULL);
	return (ft_bzero(ret, total));
}
