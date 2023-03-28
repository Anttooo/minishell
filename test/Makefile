NAME = test

LIBFT = libft.a	

SRC = main.c

SRC_O = $(SRC:.c=.o)

INCLUDES = minishell.h

FLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC_O)
	make -C libft
	cc -c $(SRC)
	cc $(FLAGS) $(SRC_O) -L libft -lft -o $(NAME)

clean:
	make clean -C libft
	rm -f $(SRC_O)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
