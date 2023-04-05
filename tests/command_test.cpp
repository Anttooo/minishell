#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"
#include <iostream>


extern "C" {
#include "../include/command.h"
#include "../include/minishell.h"
}

extern t_data	g_data;
extern char		**environ;

void init_g_data() {
    // Initialize the g_data struct here, for example:
	g_data.dir.start = (char *)malloc(1024);
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
    g_data.dir.builtins = ft_strdup(ft_strjoin(g_data.dir.start, "/builtins/executables/"));
	g_data.env.paths = get_paths();
	g_data.env.vars = get_env_vars(environ);
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

// Tests for get_command_path()
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

// Tests for get_cmd_count()
TEST(CommandTestGroup, CountCommands1)
{
	g_data.cur.raw = "echo hello";
	get_cmd_count();
	CHECK_EQUAL(1, g_data.cur.cmd_count);
}

TEST(CommandTestGroup, CountCommands2)
{
	g_data.cur.raw = "echo \"so many pipes |||| but they are in double quotes\" ";
	get_cmd_count();
	CHECK_EQUAL(1, g_data.cur.cmd_count);
}

TEST(CommandTestGroup, CountCommands3)
{
	g_data.cur.raw = "echo \'so many pipes |||| but they are in single quotes\' ";
	get_cmd_count();
	CHECK_EQUAL(1, g_data.cur.cmd_count);
}

TEST(CommandTestGroup, CountCommands4)
{
	g_data.cur.raw = "ls -l | grep 'test'";
	get_cmd_count();
	CHECK_EQUAL(2, g_data.cur.cmd_count);
}

TEST(CommandTestGroup, CountCommands5)
{
	g_data.cur.raw = "cat \'so many pipes |||| but they are in single quotes\' | grep 'test'";
	get_cmd_count();
	CHECK_EQUAL(2, g_data.cur.cmd_count);
}

// Tests for parse_each_command()
// TEST(CommandTestGroup, ParseEachCommand1)
// {
// 	// initialisation
// 	g_data.cur.raw = "cat \'so many pipes |||| but they are in single quotes\' | grep 'test'";
// 	get_cmd_count();
// 	allocate_cmd_list();
// 	parse_each_command();
// 	CHECK_EQUAL("cat", g_data.cur.cmd_list[0]->cmd);
// 	CHECK_EQUAL("grep", g_data.cur.cmd_list[1]->cmd);
// }

TEST(CommandTestGroup, ParseEachCommand2)
{
	// initialisation
	g_data.cur.raw = "cat \'so many pipes |||| but they are in single quotes\'";
	get_cmd_count();
	allocate_cmd_list();
	parse_each_command();
	CHECK_EQUAL("cat", g_data.cur.cmd_list[0]->cmd);
}


IMPORT_TEST_GROUP(CommandTestGroup);
