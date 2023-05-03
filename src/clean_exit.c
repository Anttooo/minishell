#include "../include/minishell.h"

extern t_data g_data;

void	free_arr(char **arr)
{
	int	idx;
	
	idx = -1;
	while (arr[++idx] != NULL)
		free(arr[idx]);
	free(arr);
}

void	clean_exit(void)
{
	if (g_data.dir.current != g_data.dir.start && g_data.dir.start)
	{
		if (chdir(g_data.dir.start) == -1)
		{
			perror("chdir error in clean_exit");
		}
	}
	if (g_data.dir.start)
	{
		free (g_data.dir.start);
		g_data.dir.start = NULL;
	}
	if (g_data.dir.builtins)
	{
		free (g_data.dir.builtins);
		g_data.dir.start = NULL;
	}
	if (g_data.env.user)
	{
		free (g_data.env.user);
		g_data.env.user = NULL;
	}
	if (g_data.env.prompt)
	{
		free(g_data.env.prompt);
		g_data.env.prompt = NULL;
	}
}