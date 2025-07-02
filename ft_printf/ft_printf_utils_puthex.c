/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_puthex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:50:13 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/14 20:21:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned int n)
{
	int	order;

	order = 0;
	if (!n)
		return (1);
	while (n != 0)
	{
		n /= 16;
		order++;
	}
	return (order);
}

static int	ft_puthex_left(unsigned int n, t_flags *flags, int l_case)
{
	int		count;
	int		len;
	char	prefix;

	count = 0;
	len = ft_hexlen(n);
	if (flags->hash && n)
	{
		prefix = l_case * 'x' + !l_case * 'X';
		count += ft_putchar('0') + ft_putchar(prefix);
	}
	if (flags->precision != -1)
		count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_puthex(n, l_case);
	count += ft_pad(flags->width - count, ' ');
	return (count);
}

static int	ft_puthex_regular(int n, t_flags *flags, int l_case)
{
	int		len;
	int		count;
	int		p_len;

	count = 0;
	len = ft_hexlen(n);
	p_len = len;
	if (flags->precision > len)
		p_len = flags->precision;
	if (flags->width > p_len)
		count += ft_pad(flags->width - p_len - ((flags->hash && n) * 2), ' ');
	if (flags->hash && n)
	{
		count += ft_putchar('0');
		count += ft_putchar(l_case * 'x' + !l_case * 'X');
	}
	count += ft_pad(flags->precision - len, '0');
	if (!(!flags->precision && !n))
		count += ft_puthex(n, l_case);
	else if (flags->width)
		count += ft_putchar(' ');
	return (count);
}

static int	ft_puthex_zero(unsigned int n, t_flags *flags, int l_case)
{
	int	count;
	int	len;

	count = 0;
	len = ft_hexlen(n);
	if (flags->precision != -1)
		return (ft_puthex_regular(n, flags, l_case));
	if (flags->hash && n)
	{
		count += ft_putchar('0');
		count += ft_putchar(l_case * 'x' + !l_case * 'X');
	}
	count += ft_pad(flags->width - len - count, '0');
	if (!(!flags->precision && !n))
		count += ft_puthex(n, l_case);
	else if (flags->width)
		count += ft_putchar(' ');
	return (count);
}

int	ft_puthex_wrapper(unsigned int n, t_flags *flags, int l_case)
{
	if (flags->left)
		return (ft_puthex_left(n, flags, l_case));
	if (flags->zero)
		return (ft_puthex_zero(n, flags, l_case));
	return (ft_puthex_regular(n, flags, l_case));
}
