# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 04:30:00 by amagno-r          #+#    #+#              #
#    Updated: 2025/07/03 20:58:38 by amagno-r         ###   ########.fr        #
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

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: CFLAGS += -DBONUS
bonus: $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
	
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR) --no-print-directory

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning executable and libraries...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Everything cleaned!$(NC)"

re: fclean all

# Debug build
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: re

# Help target
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  all          - Build the project"
	@echo "  clean        - Remove object files"
	@echo "  fclean       - Remove object files and executable"
	@echo "  re           - Rebuild the project"
	@echo "  test         - Run basic test"
	@echo "  test_complex - Run complex pipeline test"
	@echo "  clean_test   - Clean test files"
	@echo "  valgrind     - Run memory leak check"
	@echo "  debug        - Build with debug flags and AddressSanitizer"
	@echo "  help         - Show this help message"

.PHONY: all clean fclean re test test_complex clean_test valgrind debug help
