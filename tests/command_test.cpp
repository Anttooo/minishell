#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"
#include <iostream>


extern "C" {
#include "../include/command.h"
#include "../include/minishell.h"
}

extern t_data	g_data;

void init_g_data() {
    // Initialize the g_data struct here, for example:
	g_data.dir.start = (char *)malloc(1024);
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
    g_data.dir.builtins = ft_strdup(ft_strjoin(g_data.dir.start, "/builtins/executables/"));
    // ... and so on
}

TEST_GROUP(CommandTestGroup)
{
	void	setup() {
		init_g_data();
	}
	// void	teardown() {
	// 	clean_exit();
	// }
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

IMPORT_TEST_GROUP(CommandTestGroup);
