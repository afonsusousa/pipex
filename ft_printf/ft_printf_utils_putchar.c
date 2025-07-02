/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_putchar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:54:07 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 20:06:37 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putchar_wrapper(char c, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->left)
		count += ft_putchar(c) + ft_pad(--flags->width, ' ');
	else
		count += ft_pad(--flags->width, ' ') + ft_putchar(c);
	return (count);
}
