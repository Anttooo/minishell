
#ifndef DEBUG_H
# define DEBUG_H

#include "minishell.h"

// add functions here 
void	debug_print_list(char	**list, const char *func_name);
void	debug_print_string(char *string, const char *func_name);
void	debug_print_tokens(void);
void	debug_print_commands(void);

#endif