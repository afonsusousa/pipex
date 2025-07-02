# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 04:30:00 by amagno-r          #+#    #+#              #
#    Updated: 2025/07/01 23:04:01 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = pipex

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./libft 

# Source files
SRCS = pipex.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(NC)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft built successfully!$(NC)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(RED)Cleaning executable and libraries...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Everything cleaned!$(NC)"

re: fclean all

# Test targets
test: $(NAME)
	@echo "$(YELLOW)Running basic test...$(NC)"
	@echo "This is a test file" > test_input.txt
	@echo "line 2" >> test_input.txt
	@echo "line 3" >> test_input.txt
	@./$(NAME) test_input.txt "cat" "wc -l" test_output.txt
	@echo "$(GREEN)Test completed. Check test_output.txt$(NC)"

test_complex: $(NAME)
	@echo "$(YELLOW)Running complex pipeline test...$(NC)"
	@ls -la > test_input.txt
	@./$(NAME) test_input.txt "grep pipex" "wc -l" test_output.txt
	@echo "$(GREEN)Complex test completed. Check test_output.txt$(NC)"

clean_test:
	@rm -f test_input.txt test_output.txt

# Valgrind memory check
valgrind: $(NAME)
	@echo "$(YELLOW)Running valgrind memory check...$(NC)"
	@echo "Test content for valgrind" > test_input.txt
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) test_input.txt "cat" "wc -l" test_output.txt
	@rm -f test_input.txt test_output.txt

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
