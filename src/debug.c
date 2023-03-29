

#include "../include/debug.h"

void	debug_print_list(char	**list, const char *func_name)
{
	printf("Debugging list in function %s:\n", func_name);
	for (int i = 0; list[i] != NULL; i++)
	{
		printf("%s	\n", list[i]);
	}
}

void	debug_print_string(char *string, const char *func_name)
{
	printf("Debugging string in function %s:\n", func_name);
	printf("string: %s\n", string);
}