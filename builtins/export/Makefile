# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 20:17:43 by joonasmykka       #+#    #+#              #
#    Updated: 2023/03/31 07:24:55 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = export

SRC = export.c

SRC_O = $(SRC:.c=.o)

INCLUDES = export.h

FLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC_O)
	cc -c $(SRC)
	cc $(FLAGS) $(SRC_O) -o $(BUILTINS_OUT)/$(NAME)

clean:
	rm -f $(SRC_O)

fclean: clean
	rm -f $(BUILTINS_OUT)/$(NAME)

re: fclean all
