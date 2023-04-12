

#include "../include/debug.h"

extern	t_data	g_data;

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

void	debug_print_tokens(const char *func_name)
{
	printf("Debugging string in function %s:\n", func_name);
	for (int i = 0; g_data.cur.tokens[i] != NULL; i++)
	{
		printf("\n----- Token %d -----\nToken: %s\nType: %s	\n", i, g_data.cur.tokens[i]->token, g_data.cur.tokens[i]->type);
	}
}