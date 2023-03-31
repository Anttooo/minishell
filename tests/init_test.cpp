#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"

extern "C" {
#include "init.h"
#include "minishell.h"
#include "debug.h"
}

extern t_data g_data;

TEST_GROUP(InitialisationTestGroup)
{
};

TEST(InitialisationTestGroup, GetPathsNotNull)
{
		char **paths = get_paths();
    CHECK(paths != NULL);
    // Free the memory allocated by get_paths()
    for (int i = 0; paths[i] != NULL; i++) {
        free(paths[i]);
    }
    free(paths);
}

TEST(InitialisationTestGroup, StartDirectoryCorrectlySet)
{
	init_struct();
	
	// Check that g_data.dir.start contains "/minishell" after initialisation
	STRCMP_CONTAINS("/minishell", g_data.dir.start);
	clean_exit();
}

TEST(InitialisationTestGroup, CurrentDirectoryEqualsHomeAfterInit)
{
	CHECK_EQUAL(NULL, g_data.dir.current);
	
	init_struct();
	
	// Check that g_data.dir.current equals getenv("HOME") after init
	STRCMP_EQUAL(getenv("HOME"), g_data.dir.current);
	clean_exit();
}

IMPORT_TEST_GROUP(InitialisationTestGroup);