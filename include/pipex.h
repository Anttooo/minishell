/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:46:59 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/11 10:29:44 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include "minishell.h"
# include <sys/types.h>

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

void	pipex(void);
void	init(t_pipes *p);
void	execute_cmd(t_pipes *p);
void	pipes_and_forks(t_pipes *p);

#endif
