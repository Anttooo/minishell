#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"

extern "C" {
#include "init.h"
#include "debug.h"
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

IMPORT_TEST_GROUP(GetPathsTestGroup);