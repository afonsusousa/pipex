/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_puts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:38:34 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/10 02:09:22 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	while (str && *str)
		count += ft_putchar(*str++);
	return (count);
}

int	ft_putnstr(char *str, int n)
{
	int	count;

	count = 0;
	while (str && *str && n--)
		count += ft_putchar(*str++);
	return (count);
}
