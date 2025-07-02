/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_putunbr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:51:05 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 21:21:59 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unumlen(unsigned int n)
{
	int	order;

	order = 0;
	if (!n)
		return (1);
	while (n != 0)
	{
		n /= 10;
		order++;
	}
	return (order);
}

static int	ft_putunbr_left(unsigned int n, t_flags *flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_unumlen(n);
	if (flags->precision != -1)
		count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putunbr(n);
	else if (flags->width)
		count += ft_putchar(' ');
	count += ft_pad(flags->width - count, ' ');
	return (count);
}

static int	ft_putunbr_regular(unsigned int n, t_flags *flags)
{
	int	len;
	int	count;
	int	p_len;

	count = 0;
	len = ft_unumlen(n);
	p_len = len;
	if (flags->precision > len)
		p_len = flags->precision;
	if (flags->sign || flags->space)
		p_len++;
	count += ft_pad(flags->width - p_len, ' ');
	count += ft_space_sign((long int) n, flags);
	count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putunbr(n);
	else if (flags->width)
		count += ft_putchar(' ');
	return (count);
}

static int	ft_putunbr_zero(unsigned int n, t_flags *flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_unumlen(n);
	if (flags->precision != -1)
		return (ft_putunbr_regular(n, flags));
	if (flags->sign || flags->space)
		len++;
	count += ft_space_sign((long int) n, flags);
	count += ft_pad(flags->width - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putunbr(n);
	return (count);
}

int	ft_putunbr_wrapper(int n, t_flags *flags)
{
	if (flags->left)
		return (ft_putunbr_left(n, flags));
	if (flags->zero)
		return (ft_putunbr_zero(n, flags));
	return (ft_putunbr_regular(n, flags));
}
