# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 11:19:19 by kanykei           #+#    #+#              #
#    Updated: 2024/06/27 15:00:34 by kanykei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Target =================================== #
NAME		:= libft.a

# ================================ Sources =================================== #

SRC			:= ft_memset.c ft_memcpy.c ft_strcmp.c ft_append_array.c \
				ft_strdup.c ft_strlen.c ft_strjoin.c

# ================================ Flags ===================================== #
OBJ			:= $(addprefix obj/,$(notdir $(SRC:.c=.o)))
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror

# ================================ Rules ===================================== #

.SILENT:

all: $(NAME)

$(NAME)		: $(OBJ)
			ar rcs $(NAME) $(OBJ)

obj/%.o		: %.c | obj
			$(CC) $(CFLAGS) -c $< -o $@

obj			:
			mkdir obj

clean		:
			rm -rf obj

fclean		: clean
			rm $(NAME)

re: fclean all

.PHONY		:	all clean fclean re 