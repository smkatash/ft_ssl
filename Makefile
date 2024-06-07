# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 11:19:19 by kanykei           #+#    #+#              #
#    Updated: 2024/06/07 14:56:17 by kanykei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Target =================================== #
NAME		:= ft_ssl

# ================================ Sources =================================== #

VPATH		:= src

SRC			:= main.c parser.c md5.c md5-utils.c

# ================================ Flags ===================================== #
OBJ			:= $(addprefix obj/,$(notdir $(SRC:.c=.o)))
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror #-fsanitize=address

# ============================== Libraries ==================================== #
INCFL		:=	-I./include 

# ================================ Rules ===================================== #
.SILENT:

all: $(NAME) 

$(NAME)		: $(OBJ)
			$(CC) $(OBJ) -o $(NAME)
			@echo "\033[1;32m ft_ssl is compiled \033[0m"

obj/%.o		: %.c | obj
			$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj			:
			mkdir obj

clean		:
			rm -rf obj
			@echo "deleting object files..."

fclean		: clean
			rm $(NAME)
			@echo "deleting ft_ssl..."

re			: clean all

.PHONY		:	all clean fclean re 
