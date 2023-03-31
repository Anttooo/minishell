#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"

extern "C" {
#include "../builtins/export/export.h"
#include "minishell.h"
}

TEST_GROUP(ExportTestGroup)
{
};

// Test that export prints out all the varibles in argv
TEST(ExportTestGroup, output)
{
  	// Set up the command to execute the export executable with arguments
    char command[1024];
    sprintf(command, "./builtins/executables/export VAR1=test VAR2=test VAR3=test");

    // Open a pipe to capture the output of the command
    FILE* pipe = popen(command, "r");
    char buffer[1024];

    // Read the output of the command into the buffer
    fgets(buffer, 1024, pipe);

    // Close the pipe
    pclose(pipe);

    // Check that the correct output was printed
    STRCMP_EQUAL("VAR1=test\nVAR2=test\nVAR3=test\n", buffer);
}

IMPORT_TEST_GROUP(ExportTestGroup);