#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int main(void)
{
    char *input;

    while (42) {
        input = readline("Supershell >> ");
        if (!input) 
		{
            printf("\n");
        }
		else 
		{
			printf("You entered: %s\n", input);
		}

        if (strcmp(input, "quit") == 0) 
		{
            free(input);
            break;
        }
		
        free(input);
    }
    return (0);
}
