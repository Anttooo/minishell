#include "../include/minishell.h"

extern t_data g_data;

void	clean_exit(void)
{
	if (g_data.dir.start)
	{
		free (g_data.dir.start);
		g_data.dir.start = NULL;
	}

	// TODO: set the pwd to the starting directory before the program quits.
}