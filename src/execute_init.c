/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:32:23 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 17:55:18 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

void	redir_input(t_pipes *p)
{
	p->fdin = open(g_data.cur.input, O_RDONLY);
	if (p->fdin < 0)
	{
		perror("input file");
		clean_exit_shell();
		exit(1);
	}
}

void	redir_out(t_pipes *p)
{
	if (g_data.cur.output_mode == APPEND_MODE)
		p->fdout = open(g_data.cur.output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (g_data.cur.output_mode == OVERWRITE_MODE)
		p->fdout = open(g_data.cur.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		perror("invalid output mode");
		clean_exit_shell();
		exit(1);
	}
	if (p->fdout < 0)
	{
		perror("output file");
		clean_exit_shell();
		exit(1);
	}
}

