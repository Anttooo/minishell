/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:52:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 14:04:58 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

void	handle_input_redirection_for_execution(t_pipes *p)
{
	if (p->idx == 0)
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
