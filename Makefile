# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oruban <oruban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/25 15:10:17 by beredzhe          #+#    #+#              #
#    Updated: 2024/06/03 16:35:42 by oruban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# List all source files
SRCS	=	$(wildcard src/main/*.c) \
			$(wildcard src/tokenization/*.c) \
			$(wildcard src/utils/*.c) \
			$(wildcard src/lexer/*.c) \
			$(wildcard src/expand/*c) \
			$(wildcard src/execution/*.c) # roi

# Generate object files names
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
LDLIBS	=	-lreadline -lft # This tells the linker to link the Readline library with your program
LDFLAGS	+=	-L./libft


# Generate object files names
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_A	=	libft/libft.a
HEADER	=	$(wildcard *.h) $(wildcard ./includes/*.h) #roi corrected
VPATH	=	src/main:src/tokenization:src/utils
INCLUDE	=	-I ./ -I ./includes

# print:
# 	echo $(HEADER)

all: $(NAME)

run: $(NAME)
	@./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean --silent --directory=./libft
	@echo "\033[31mCleaned!\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make clean --silent --directory=./libft
	@echo "\033[31mFull cleaned!\033[0m"

re: fclean all

$(LIBFT_A):
	@make --directory=./libft

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	@echo "\033[32mProject successfully compiled!\033[0m"

# Rule to compile each .c file into .o file in the obj directory
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

leak: all
	valgrind --suppressions=./local.supp --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

