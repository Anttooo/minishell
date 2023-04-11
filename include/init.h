#ifndef INIT_H
# define INIT_H

# include "../libft/libft.h"
# include <fcntl.h>

char	**get_env_vars(char **envp);
void	init_for_new_input(void);
int		init_struct(char **envp);
char	**get_paths(void);

#endif