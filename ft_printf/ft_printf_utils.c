/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:53:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 21:20:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pad(int len, char pad)
{
	int	count;

	count = 0;
	if (len <= 0)
		return (0);
	while (len--)
		count += ft_putchar(pad);
	return (count);
}

int	ft_space_sign(long int n, t_flags *flags)
{
	if (n < 0)
		return (ft_putchar('-'));
	if (flags->sign)
		return (ft_putchar('+'));
	if (flags->space)
		return (ft_putchar(' '));
	return (0);
}

int	is_spec(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}
