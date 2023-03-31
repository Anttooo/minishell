#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"

extern "C" {
#include "execute.h"
#include "debug.h"
}

TEST_GROUP(ExecuteCommandTestGroup)
{
};

TEST(ExecuteCommandTestGroup, EchoHelloTest)
{
	int original_stdout = dup(STDOUT_FILENO);
    const char *temp_output_file = "temp_output.txt";
    int temp_fd = open(temp_output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Redirect stdout to the temporary file
    dup2(temp_fd, STDOUT_FILENO);

    // Call the execute_command function with the "echo" command and "Hello" as an argument
    char *args[] = {"echo", "Hello", NULL};
	execute_command("/bin/echo", NULL, args);

    // Restore stdout to its original state
    dup2(original_stdout, STDOUT_FILENO);
    close(temp_fd);

    // Read the content of the temporary file
    FILE *file = fopen(temp_output_file, "r");
    if (file == NULL)
    {
        FAIL("Failed to open temporary output file");
    }

    char output[32];
    fgets(output, sizeof(output), file);
    fclose(file);
    // Remove the temporary file
    remove(temp_output_file);

    // Check if the captured output matches the expected output
    STRCMP_EQUAL("Hello\n", output);
}

IMPORT_TEST_GROUP(ExecuteCommandTestGroup);
