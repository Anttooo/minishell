# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 20:17:43 by joonasmykka       #+#    #+#              #
#    Updated: 2023/03/31 08:23:15 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = echo

SRC = echo.c

SRC_O = $(SRC:.c=.o)

INCLUDES = echo.h

FLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC_O)
	cc -c $(SRC)
	cc $(FLAGS) $(SRC_O) -o $(NAME)

clean:
	rm -f $(SRC_O)

fclean: clean
	rm -f $(NAME)

re: fclean all
