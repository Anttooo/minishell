#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"

extern "C" {
#include "command.h"
}

TEST_GROUP(GetPathsTestGroup)
{
};

TEST(GetPathsTestGroup, GetPathsNotNull)
{
    char **paths = get_paths();
    CHECK(paths != NULL);
    // Free the memory allocated by get_paths()
    for (int i = 0; paths[i] != NULL; i++) {
        free(paths[i]);
    }
    free(paths);
}

TEST_GROUP(GetCommandPathTestGroup)
{
};

TEST(GetCommandPathTestGroup, ValidCommand)
{
    char *valid_command = "ls";
    char *command_path = get_command_path(valid_command);
    CHECK(command_path != NULL);
    free(command_path);
}

TEST(GetCommandPathTestGroup, InvalidCommand)
{
    char *invalid_command = "non_existent_command";
    char *command_path = get_command_path(invalid_command);
    CHECK(command_path == NULL);
}

TEST_GROUP(ParseInputTestGroup)
{
};

// TEST(ParseInputTestGroup, ValidInput)
// {
//     char *valid_input = "ls -la";
//     int result = parse_input(valid_input);
//     CHECK_EQUAL(0, result);
// }

TEST(ParseInputTestGroup, InvalidInput)
{
    char *invalid_input = "non_existent_command -arg";
    int result = parse_input(invalid_input);
    CHECK_EQUAL(-1, result);
}

IMPORT_TEST_GROUP(GetPathsTestGroup);
IMPORT_TEST_GROUP(GetCommandPathTestGroup);
IMPORT_TEST_GROUP(ParseInputTestGroup);
