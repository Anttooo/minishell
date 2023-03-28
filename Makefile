CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L/Users/oanttoor/.brew/Cellar/cpputest/4.0/lib -lCppUTest -lCppUTestExt

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c, obj/%.o, $(SRC_FILES))

TEST_SRC_FILES = $(wildcard tests/*.cpp) tests/AllTests.cpp
TEST_OBJ_FILES = $(patsubst tests/%.cpp, obj/%.o, $(TEST_SRC_FILES))

.PHONY: all
all: tests_run

.PHONY: clean
clean:
	rm -f obj/* bin/*

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/tests_run: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $^ $(LDFLAGS) -o $@

.PHONY: tests_run
tests_run: bin/tests_run
	./bin/tests_run