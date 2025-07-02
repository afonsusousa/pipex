/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:27:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/10 16:29:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_flags(t_flags *flags)
{
	flags->left = 0;
	flags->zero = 0;
	flags->precision = -1;
	flags->hash = 0;
	flags->space = 0;
	flags->sign = 0;
	flags->width = 0;
}

static int	ft_printf_atoi(char **format)
{
	int	ret;

	ret = 0;
	if (**format == '.')
		(*format)++;
	while (**format && **format >= '0' && **format <= '9')
		ret = ret * 10 + (*((*format)++) - '0');
	return (ret);
}

void	ft_parse_flags(char **format, t_flags *flags)
{
	while (**format && !is_spec(**format))
	{
		if (**format == '+')
			flags->sign = 1;
		else if (**format == '-')
			flags->left = 1;
		else if (**format == '#')
			flags->hash = 1;
		else if (**format == '0' && !flags->left)
			flags->zero = 1;
		else if (**format == ' ')
			flags->space = 1;
		else if (**format >= '1' && **format <= '9')
		{
			flags->width = ft_printf_atoi(format);
			continue ;
		}
		else if (**format == '.')
		{
			flags->precision = ft_printf_atoi(format);
			continue ;
		}
		(*format)++;
	}
}
