#include "pipex.h"

int	parse_inputs(int argc, char **argv, t_data *data)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	data->commands = (char**)malloc((argc - 3) * sizeof(char *));
	if (data->commands == NULL)
	{
		ft_printf("Malloc failed.\n");
		return (1);
	}
	data->infile = argv[i++];
	while (i < argc - 1)
		data->commands[j++] = argv[i++];
	data->outfile = argv[i];
	return (0);
}

void	free_data(t_data *data)
{
	if (data->commands)
	{
		free (data->commands);
		data->commands = NULL;
	}
}