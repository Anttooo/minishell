/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:53:39 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/08 16:17:36 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

void handle_child(t_pipes *p)
{
	handle_input_redirection_for_execution(p);
	handle_output_redirection_for_execution(p);
    if (p->idx < g_data.cur.cmd_count - 1)
    {
        close(p->pipes[p->idx][READ_END]);
        if (p->pipes[p->idx][WRITE_END] != STDOUT_FILENO)
        {
            dup2(p->pipes[p->idx][WRITE_END], STDOUT_FILENO);
            close(p->pipes[p->idx][WRITE_END]);
        }
    }
    execute_cmd(p, p->idx);
}

void handle_parent(t_pipes *p)
{
    if (p->idx < g_data.cur.cmd_count - 1)
    {
        close(p->pipes[p->idx][WRITE_END]);
        p->fdin = p->pipes[p->idx][READ_END];
        dup2(p->fdin, STDIN_FILENO);
        close(p->pipes[p->idx][READ_END]);
    }
}
