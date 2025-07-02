# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 16:47:35 by amagno-r          #+#    #+#              #
#    Updated: 2025/05/09 01:17:25 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = 	ft_printf.c \
		ft_printf_utils_address.c \
		ft_printf_utils.c \
		ft_printf_utils_flags.c \
		ft_printf_utils_putchar.c \
		ft_printf_utils_puthex.c \
		ft_printf_utils_putnbr.c \
		ft_printf_utils_putn.c \
		ft_printf_utils_puts.c \
		ft_printf_utils_putunbr.c \
		ft_printf_utils_strs.c	

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

bonus : all

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
