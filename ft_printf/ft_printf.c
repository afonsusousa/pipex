/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 02:11:22 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 20:13:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	ft_putspecifier(char c, va_list args, t_flags *flags)
{
	if (c == 'c')
		return (ft_putchar_wrapper(va_arg(args, int), flags));
	if (c == 's')
		return (ft_putstr_wrapper(va_arg(args, char *), flags));
	if (c == 'p')
		return (ft_address_wrapper(va_arg(args, void *), flags));
	if (c == 'd')
		return (ft_putnbr_wrapper(va_arg(args, int), flags));
	if (c == 'i')
		return (ft_putnbr_wrapper(va_arg(args, int), flags));
	if (c == 'u')
		return (ft_putunbr_wrapper(va_arg(args, unsigned int), flags));
	if (c == 'x')
		return (ft_puthex_wrapper(va_arg(args, int), flags, LOWERCASE));
	if (c == 'X')
		return (ft_puthex_wrapper(va_arg(args, int), flags, UPPERCASE));
	if (c == '%')
		return (ft_putchar('%'));
	return (ft_putchar(c));
}

static int	ft_parse_spec(char **format, va_list args)
{
	int		count;
	t_flags	flags;

	count = 0;
	ft_init_flags(&flags);
	ft_parse_flags(format, &flags);
	count += ft_putspecifier(*((*format)++), args, &flags);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	char		*fmt;
	va_list		args;

	count = 0;
	fmt = (char *) format;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*fmt)
	{
		if (*fmt == '%' && *(++fmt))
			count += ft_parse_spec(&fmt, args);
		else if (*fmt == '%' && !*(fmt + 1))
			break ;
		else
			count += ft_putchar(*fmt++);
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	char *args = ">------------<%030x>------------<";
// 	int num = 123;
// 	int printed = ft_printf(args, num);
// 	printf("%d\n", printed);
// 	printed = printf(args, num);
// 	printf("%d\n", printed);
// }
