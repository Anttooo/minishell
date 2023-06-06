/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:53:39 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 16:35:46 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

void	handle_child(t_pipes *p)
{
	handle_input_redirection_for_execution(p);
	if (p->idx < g_data.cur.cmd_count - 1)
	{
		close(p->pipes[p->idx][READ_END]);
		if (p->pipes[p->idx][WRITE_END] != STDOUT)
		{
			dup2(p->pipes[p->idx][WRITE_END], STDOUT);
			close(p->pipes[p->idx][WRITE_END]);
		}
	}
	handle_output_redirection_for_execution(p);
	execute_cmd(p, p->idx);
}

void handle_parent(t_pipes *p)
{
	if (p->fdin != STDIN)
	{
		close(p->fdin);
	}
	if (p->idx < g_data.cur.cmd_count - 1)
	{
		close(p->pipes[p->idx][WRITE_END]);
		p->fdin = p->pipes[p->idx][READ_END];
	}
	else if (p->idx == g_data.cur.cmd_count - 1)
	{
		dup2(p->fdin, STDIN);
		close(p->fdin);
	}
}

