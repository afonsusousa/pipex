# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 04:30:00 by amagno-r          #+#    #+#              #
#    Updated: 2025/07/03 22:14:27 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = pipex

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./lib/libft

# Source files
SRCS =	srcs/mandatory/main.c \
		srcs/mandatory/pipex.c \
		srcs/mandatory/pipex_utils.c \
		srcs/mandatory/cmds.c \
		srcs/mandatory/frees.c \
		srcs/mandatory/str_utils.c \
		lib/get_next_line/get_next_line.c \
		lib/get_next_line/get_next_line_utils.c

BONUS_SRCS = srcs/bonus/main.c \
			srcs/bonus/pipex.c \
			srcs/bonus/pipex_utils.c \
			srcs/bonus/cmds.c \
			srcs/bonus/here_doc.c \
			srcs/bonus/frees.c \
			srcs/bonus/str_utils.c \
			lib/get_next_line/get_next_line.c \
			lib/get_next_line/get_next_line_utils.c
# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Libft
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: CFLAGS += -DBONUS
bonus: $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	
$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) --no-print-directory

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "✓ Object files cleaned!"

fclean: clean
	@echo "Cleaning executable and libraries..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "✓ Everything cleaned!"

re: fclean all

# Debug build
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: re

.PHONY: all clean fclean re test test_complex clean_test valgrind debug help
