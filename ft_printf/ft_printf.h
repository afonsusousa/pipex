/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:35:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/05/13 21:22:40 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define UPPERCASE 0
# define LOWERCASE 1

# define U_STR "0123456789ABCDEF"
# define L_STR "0123456789abcdef"

typedef struct s_flags
{
	int	left;
	int	zero;
	int	precision;
	int	hash;
	int	space;
	int	sign;
	int	width;
}	t_flags;

/* Core printf functions */
int		ft_printf(const char *format, ...);

void	ft_init_flags(t_flags *flags);
void	ft_parse_flags(char **format, t_flags *flags);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnstr(char *str, int n);
int		ft_putstr_wrapper(char *str, t_flags *flags);
int		ft_putchar_wrapper(char c, t_flags *flags);
int		ft_pad(int len, char pad);
int		ft_space_sign(long int n, t_flags *flags);
int		is_spec(char c);
int		ft_putabsnbr(int n);
int		ft_putnbr_wrapper(int n, t_flags *flags);
int		ft_putunbr(unsigned int n);
int		ft_putunbr_wrapper(int n, t_flags *flags);
int		ft_puthex(unsigned int n, int l_case);
int		ft_puthex_wrapper(unsigned int n, t_flags *flags, int l_case);
int		ft_address_wrapper(void *p, t_flags *flags);

#endif
