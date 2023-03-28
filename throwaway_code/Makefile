NAME = push_swap

SRC = main.c rules_p.c rules_r.c rules_rr.c rules_s.c check_args.c tools.c\
sort.c sort_medium.c sort_algo.c sort_algo_tools.c algo_find_spot.c\
sort_moves.c calc_moves.c a_moves.c create_stack_tools.c fake_atoi.c

SRC_O = $(SRC:.c=.o)

INCLUDES = push_swap.h

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

