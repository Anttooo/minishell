#ifndef INIT_H
# define INIT_H

# include "../libft/libft.h"
# include <fcntl.h>

void	reset_cur(void);
char	**get_paths(void);
int		init_struct(char **envp);
char	*find_env_var(char *str);
char	**get_env_vars(char **envp);

#endif