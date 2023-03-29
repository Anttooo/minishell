
#include "../include/input.h"

// Returns 1 if input is handled, executed and saved
// otherwise returns -1
int	handle_input(char *input)
{
	if (strcmp(input, "quit") == 0) 
	{
		free(input);
		quit(1);
	}
	return (1);
}