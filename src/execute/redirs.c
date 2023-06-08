/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:52:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/08 16:20:17 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

void	redir_input(t_pipes *p)
{
	p->fdin = open(g_data.cur.cmd_list[p->idx]->input, O_RDONLY);
	if (p->fdin < 0)
	{
		perror("input file");
		clean_exit_shell();
		exit(1);
	}
}

void	redir_out(t_pipes *p)
{
	if (g_data.cur.cmd_list[p->idx]->output_mode == APPEND_MODE)
		p->fdout = open(g_data.cur.cmd_list[p->idx]->output,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (g_data.cur.cmd_list[p->idx]->output_mode == OVERWRITE_MODE)
	{
		p->fdout = open(g_data.cur.cmd_list[p->idx]->output,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
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

void	handle_input_redirection_for_execution(t_pipes *p)
{
	if (g_data.cur.cmd_list[p->idx]->input == NULL)
		p->fdin = STDIN;
	else
		redir_input(p);
	if (p->fdin != STDIN)
	{
		dup2(p->fdin, STDIN);
		close(p->fdin);
	}
}

void	handle_output_redirection_for_execution(t_pipes *p)
{
	p->out_redirected = FALSE;
	if (g_data.cur.cmd_list[p->idx]->output == NULL)
	{
		p->fdout = STDOUT;
	}
	else
	{
		redir_out(p);
		p->out_redirected = TRUE;
	}
	if (p->fdout != STDOUT)
	{
		dup2(p->fdout, STDOUT);
		close(p->fdout);
	}
}
