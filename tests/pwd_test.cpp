#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"

extern "C" {
#include "builtins/pwd/pwd.h"
}

TEST_GROUP(PwdTestGroup)
{
	void teardown() {
		clean_exit();
	}
};

// TODO Create test that tests og pwd and our pwd output in multpiple dir's and situations.
TEST(PwdTestGroup, output)
{
}

IMPORT_TEST_GROUP(PwdTestGroup);