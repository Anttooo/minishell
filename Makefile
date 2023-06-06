NAME = minishell
CC = gcc
CXX = g++
FLAGS = -Wall -Werror -Wextra
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline -L libft -lft

SRC_FILES = $(wildcard src/builtins/*.c) $(wildcard src/parser/*.c) \
			 $(wildcard src/input/*.c) $(wildcard src/execute/*.c) \
			 $(wildcard src/*.c) $(wildcard src/tokenizer/*.c)

OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c))  \
				$(patsubst src/tokenizer/%.c, obj/tokenizer/%.o, $(wildcard src/tokenizer/*.c)) \
				$(patsubst src/builtins/%.c, obj/builtins/%.o, $(wildcard src/builtins/*.c)) \
				$(patsubst src/execute/%.c, obj/execute/%.o, $(wildcard src/execute/*.c)) \
				$(patsubst src/parser/%.c, obj/parser/%.o, $(wildcard src/parser/*.c)) \
				$(patsubst src/input/%.c, obj/input/%.o, $(wildcard src/input/*.c))

.PHONY: all
all: $(NAME)

$(NAME): $(filter-out obj/AllTests.o, $(OBJ_FILES))
	make -C libft
	$(CC) -g $(LDFLAGS) $^ -o bin/$@ -lreadline

run: $(NAME)
	./bin/$(NAME)

.PHONY: clean
clean:
	make fclean -C libft	
	rm -f obj/*.o obj/*/*.o bin/*

obj/%.o: src/%.c
	$(CC) -g $(FLAGS) -c $< -o $@
