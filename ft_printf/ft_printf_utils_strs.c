/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_strs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:48:53 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 20:05:26 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	char	*start;

	start = str;
	while (str && *str)
		str++;
	return (str - start);
}

int	ft_putstr_wrapper(char *str, t_flags *flags)
{
	int	len;
	int	count;

	len = ft_strlen(str);
	count = 0;
	if (!str && (flags->precision == -1 || flags->precision >= 6))
		return (ft_putstr_wrapper("(null)", flags));
	else if (!str)
		return (ft_putstr_wrapper("", flags));
	if (flags->precision != -1 && flags->precision < len)
		len = flags->precision;
	if (flags->left)
	{
		count += ft_putnstr(str, len);
		count += ft_pad(flags->width - len, ' ');
	}
	else
	{
		count += ft_pad(flags->width - len, ' ');
		count += ft_putnstr(str, len);
	}
	return (count);
}
