
#include "../include/input.h"
#include "../include/command.h"

// Returns 1 if input is handled, executed and saved
// otherwise returns -1
int	handle_input(char *input)
{
	if (strcmp(input, "quit") == 0)
	{
		free(input);
		exit(0);
	}
	// If input is not "quit", pass input to command parsing
	else
	{
		parse_input(input);
	}
	return (1);
}