/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_address.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:22:15 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 20:07:02 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putaddress(unsigned long int n)
{
	int	count;

	count = 0;
	if (n > 15)
		count += (ft_putaddress(n / 16));
	return (count += ft_putchar((L_STR[n % 16])));
}

static int	ft_address_len(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_address_wrapper(void *p, t_flags *flags)
{
	int	count;
	int	addr_len;

	count = 0;
	addr_len = ft_address_len((unsigned long int) p) + 2;
	if (!p && !flags->precision)
		return (ft_putstr("(nil)"));
	if (!p && flags->left)
		return (ft_putstr("(nil)") + ft_pad(flags->width - 5, ' '));
	else if (!p)
		return (ft_pad(flags->width - 5, ' ') + ft_putstr("(nil)"));
	if (flags->left && p)
	{
		count += ft_putstr("0x") + ft_putaddress((unsigned long int) p);
		count += ft_pad(flags->width - addr_len, ' ');
	}
	else
	{
		count += ft_pad(flags->width - addr_len, ' ');
		count += ft_putstr("0x") + ft_putaddress((unsigned long int) p);
	}
	return (count);
}
