#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"

extern "C" {
#include "command.h"
#include "minishell.h"
}

int main(int argc, char** argv)
{
		init_struct();
		
		return CommandLineTestRunner::RunAllTests(argc, argv);
}