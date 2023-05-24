/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/24 14:16:20 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/types.h>
# include "minishell.h"

# define WRITE_END 1
# define READ_END 0
# define STDERR 2
# define STDOUT 1
# define STDIN 0

typedef struct s_pipex_data 
{
	int			fdin;
	int			fdout;
	int			pipe[2];
	int			idx;
	pid_t		pid;
}				t_pipes;

void	execute(void);
void	init(t_pipes *p);
void	execute_builtin(void);
void	execute_cmd(t_pipes *p);
void	pipes_and_forks(t_pipes *p);

#endif
