NAME = pipex

CC = cc

MAKE = make

INCLUDES = -I./libft

CFLAGS =  -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS = -L./libft -lft

DEPS = ./libft/libft.h
SRCS = $(SRCDIR)/pipex.c $(SRCDIR)/parse_input.c
SRCDIR = ./srcs
OBJDIR = ./build

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) 
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS) $(LDFLAGS)

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all
