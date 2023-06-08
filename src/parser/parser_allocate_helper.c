/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_allocate_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:21:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/08 11:22:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;

int	parser_allocate(int i)
{
	g_data.cur.cmd_list[i] = (t_cmd *)malloc(sizeof(t_cmd));
	if (!g_data.cur.cmd_list[i])
	{
		perror("");
		clean_exit_shell();
		return (1);
	}
	g_data.cur.cmd_list[i]->args = NULL;
	g_data.cur.cmd_list[i]->cmd = NULL;
	g_data.cur.cmd_list[i]->input = NULL;
	g_data.cur.cmd_list[i]->output = NULL;
	g_data.cur.cmd_list[i]->output_mode = 0;
	return (0);
}
