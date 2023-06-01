NAME = minishell
CC = gcc
CXX = g++
FLAGS =
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline -L libft -lft

SRC_FILES = $(wildcard src/*.c) $(wildcard src/tokenizer/*.c) $(wildcard src/builtins/*.c) $(wildcard src/parser/*.c) $(wildcard src/input/*.c)
OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c))  \
						$(patsubst src/tokenizer/%.c, obj/tokenizer/%.o, $(wildcard src/tokenizer/*.c)) \
						$(patsubst src/builtins/%.c, obj/builtins/%.o, $(wildcard src/builtins/*.c)) \
						$(patsubst src/parser/%.c, obj/parser/%.o, $(wildcard src/parser/*.c)) \
						$(patsubst src/input/%.c, obj/input/%.o, $(wildcard src/input/*.c))

.PHONY: all
all: $(NAME)

$(NAME): $(filter-out obj/AllTests.o, $(OBJ_FILES))
	make -C libft
	$(CC) $(LDFLAGS) $^ -o bin/$@ -lreadline

run: $(NAME)
	./bin/$(NAME)

.PHONY: clean
clean:
	make fclean -C libft	
	rm -f obj/*.o obj/*/*.o bin/*

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@
