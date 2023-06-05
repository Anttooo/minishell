/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/05 18:37:02 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "minishell.h"

# define NO_CHILDS -1
# define WRITE_END 1
# define READ_END 0
# define STDERR 2
# define STDOUT 1
# define STDIN 0

# define TRUE 1
# define FALSE 0

typedef struct s_pipex_data
{
	int			pipes[1000][2];
	int			out_redirected;
	int			fdout;
	int			fdin;
	int			idx;
	pid_t		pid;
}				t_pipes;

void	execute(void);
void	init(t_pipes *p);
void	redir_out(t_pipes *p);
int	execute_builtin(t_pipes *p);
void	redir_input(t_pipes *p);
int		what_builtin(char *cmd);
void	pipes_and_forks(t_pipes *p);
char	*get_command_path(char *token);
void    execute_cmd(t_pipes *p, int idx);

#endif
