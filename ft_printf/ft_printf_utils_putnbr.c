/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_putnbr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:20:59 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 20:06:20 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numlen(int n)
{
	int			order;
	long int	n2;

	order = 0;
	n2 = n;
	if (!n)
		return (1);
	if (n2 < 0)
		n2 = -n2;
	while (n2 != 0)
	{
		n2 /= 10;
		order++;
	}
	return (order);
}

static int	ft_putnbr_left(int n, t_flags *flags)
{
	int	count;
	int	len;

	count = ft_space_sign(n, flags);
	len = ft_numlen(n);
	if (flags->precision != -1)
		count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putabsnbr(n);
	else if (flags->width)
		count += ft_putchar(' ');
	count += ft_pad(flags->width - count, ' ');
	return (count);
}

static int	ft_putnbr_regular(int n, t_flags *flags)
{
	int	len;
	int	count;
	int	p_len;

	count = 0;
	len = ft_numlen(n);
	p_len = len;
	if (flags->precision > len)
		p_len = flags->precision;
	if (flags->sign || flags->space || n < 0)
		p_len++;
	count += ft_pad(flags->width - p_len, ' ');
	count += ft_space_sign(n, flags);
	count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putabsnbr(n);
	else if (flags->width)
		count += ft_putchar(' ');
	return (count);
}

static int	ft_putnbr_zero(int n, t_flags *flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_numlen(n);
	if (flags->precision != -1)
		return (ft_putnbr_regular(n, flags));
	if (flags->sign || flags->space || n < 0)
		len++;
	count += ft_space_sign(n, flags);
	count += ft_pad(flags->width - len, '0');
	if (!(!flags->precision && !n))
		count += ft_putabsnbr(n);
	return (count);
}

int	ft_putnbr_wrapper(int n, t_flags *flags)
{
	if (flags->left)
		return (ft_putnbr_left(n, flags));
	if (flags->zero)
		return (ft_putnbr_zero(n, flags));
	return (ft_putnbr_regular(n, flags));
}
