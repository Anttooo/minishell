#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"
#include <iostream>


extern "C" {
#include "command.h"
#include "minishell.h"
}

TEST_GROUP(CommandTestGroup)
{
};

TEST(CommandTestGroup, ValidCommand)
{
		char *valid_command = "ls";
    char *command_path = get_command_path(valid_command);
    CHECK(command_path != NULL);
    free(command_path);
}

TEST(CommandTestGroup, InvalidCommand)
{
    char *invalid_command = "non_existent_command";
    char *command_path = get_command_path(invalid_command);
    CHECK(command_path == NULL);
}

/*
TODO: this test currently fails because parse_input also executes
the command, and doing so requires setting up the global variable.
*/ 
TEST(CommandTestGroup, ValidInput)
{
    char *valid_input = "echo hello";
    int result = parse_input(valid_input);
    CHECK_EQUAL(0, result);
}

TEST(CommandTestGroup, InvalidInput)
{
    char *invalid_input2 = "pwd1";
    int result = parse_input(invalid_input2);
    CHECK_EQUAL(-1, result);
}

IMPORT_TEST_GROUP(CommandTestGroup);
