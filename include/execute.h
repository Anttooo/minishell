/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/08 16:21:34 by joonasmykka      ###   ########.fr       */
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
void	redir_input(t_pipes *p);
int		what_builtin(char *cmd);
void	handle_child(t_pipes *p);
void	handle_parent(t_pipes *p);
void	execute_builtin(t_pipes *p);
void	pipes_and_forks(t_pipes *p);
char	*get_command_path(char *token);
void	execute_cmd(t_pipes *p, int idx);
void	handle_input_redirection_for_execution(t_pipes *p);
void	handle_output_redirection_for_execution(t_pipes *p);

#endif
