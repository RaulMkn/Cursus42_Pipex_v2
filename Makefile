# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakende <rmakende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:07:40 by rmakende          #+#    #+#              #
#    Updated: 2025/06/13 17:12:10 by rmakende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
DEBUG_FLAGS = -g -fsanitize=address

# Directory structure
LIBFT_DIR   = ./Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Source files (using bonus files as main)
SRCS        = pipex_bonus.c pipex_utils_bonus.c pipex_aux.c

# Object files
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Program name
NAME        = pipex

# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[1;33m
NC          = \033[0m

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(NC)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)$(NAME) compiled!$(NC)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Clean done!$(NC)"

fclean: clean
	@echo "$(RED)Full clean...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Full clean done!$(NC)"

re: fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re debug