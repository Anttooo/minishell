#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"

extern "C" {
#include "../include/command.h"
#include "../include/minishell.h"
}

int main(int argc, char** argv)
{		
		return CommandLineTestRunner::RunAllTests(argc, argv);
}