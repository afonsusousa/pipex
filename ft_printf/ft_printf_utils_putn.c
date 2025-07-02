/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_putn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:35:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/10 02:11:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putabsnbr(int n)
{
	int			count;
	long int	nb;

	nb = n;
	count = 0;
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		count += ft_putabsnbr(nb / 10);
	return (count += ft_putchar(nb % 10 + '0'));
}

int	ft_putunbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putunbr(n / 10);
	return (count += ft_putchar(n % 10 + '0'));
}

int	ft_puthex(unsigned int n, int l_case)
{
	int	count;

	count = 0;
	if (n > 15)
		count += (ft_puthex(n / 16, l_case));
	if (l_case)
		count += ft_putchar(L_STR[n % 16]);
	else
		count += ft_putchar(U_STR[n % 16]);
	return (count);
}
