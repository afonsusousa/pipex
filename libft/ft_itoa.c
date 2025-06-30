/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:13:49 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/11 15:46:27 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_order(long int nb)
{
	int	order;

	order = 1;
	while (nb / 10 > 0)
	{
		nb /= 10;
		order++;
	}
	return (order);
}

char	*ft_itoa(int n)
{
	long int	nb;
	long int	order;
	int			sign;
	char		*ret;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
	}
	order = ft_order(nb) + sign;
	ret = (char *)ft_calloc(order + 1, 1);
	if (!ret)
		return (NULL);
	while (order)
	{
		ret[--order] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign)
		ret[0] = '-';
	return (ret);
}

/*
#include <stdio.h>
int main()
{
	printf("%d", ft_atoi(ft_itoa(2147483647)));
}
*/
