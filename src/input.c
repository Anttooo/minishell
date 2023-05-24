
#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern t_data g_data;

// TODO: add error handling 
int	handle_input(char *input)
{
	if (strcmp(input, "quit") == 0)
	{
		free(input);
		exit(0);
	}
	// If input includes <<, capture delim (next argument until delim) and start heredoc
	// Get delim
	// Start Heredoc(delim)
	// If input is not "quit", pass input to command parsing
	else
	{
    	g_data.cur.raw = ft_strdup(input);
	}
	return (0);
}

// heredoc (char delim)
// create buffer
// readline
// 