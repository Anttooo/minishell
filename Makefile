NAME = minishell
CC = gcc
CXX = g++
CFLAGS = -Iinclude -Itesting_framework/cpputest-3.8/include/CppUTest -Wall
CXXFLAGS = $(CFLAGS)
LDFLAGS = -Ltesting_framework/cpputest-3.8/cpputest_build/lib -lCppUTest -lCppUTestExt -L/opt/homebrew/opt/readline/lib -lreadline -L libft -lft

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES))

TEST_SRC_FILES = $(wildcard tests/*.cpp) tests/AllTests.cpp
TEST_OBJ_FILES = $(patsubst tests/%.cpp, obj/%.o, $(TEST_SRC_FILES))

BUILTINS_MAKE = \
make -C builtins/pwd\
make -C builtins/echo

BUILTINS_CLEAN = \
make fclean -C builtins/pwd\
make fclean -C builtins/echo

.PHONY: all
all: $(NAME)

$(NAME): $(filter-out obj/AllTests.o, $(OBJ_FILES))
	make -C libft
	$(BUILTINS_MAKE)
	$(CC) $(LDFLAGS) $^ -o bin/$@ -lreadline

run: $(NAME)
	./bin/$(NAME)

.PHONY: clean
clean:
	make fclean -C libft	
	$(BUILTINS_CLEAN)
	rm -f obj/* bin/*

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/tests_run: $(filter-out obj/main.o, $(OBJ_FILES)) $(TEST_OBJ_FILES)
	$(CXX) $^ $(LDFLAGS) -o $@

.PHONY: tests_run
tests_run: bin/tests_run
	./bin/tests_run