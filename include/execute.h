/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/05 15:27:12 by joonasmykka      ###   ########.fr       */
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
# include <sys/types.h>
# include "minishell.h"

# define NO_CHILDS -1
# define WRITE_END 1
# define READ_END 0
# define STDERR 2
# define STDOUT 1
# define STDIN 0

typedef struct s_pipex_data
{
	int			pipes[1000][2];
	int			fdout;
	int			fdin;
	int			idx;
	pid_t		pid;
}				t_pipes;

void	execute(void);
void	init(t_pipes *p);
int		execute_builtin(void);
int		what_builtin(char *cmd);
void	pipes_and_forks(t_pipes *p);
char	*get_command_path(char *token);
void    execute_cmd(t_pipes *p, int idx);

#endif
