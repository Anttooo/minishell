/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_and_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:21:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 15:44:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/debug.h"

extern t_data	g_data;

void	handle_cmd(int cmd_idx, char *token, int *args_index)
{
	g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(token);
	g_data.cur.cmd_list[cmd_idx]->args = (char **)malloc(100 * sizeof(char *));
	string_array_malloc_error_check(g_data.cur.cmd_list[cmd_idx]->args);
	g_data.cur.cmd_list[cmd_idx]->args[(*args_index)++] = ft_strdup(token);
}

void	handle_args(int cmd_idx, char *token, int *args_index)
{
	g_data.cur.cmd_list[cmd_idx]->args[*args_index] = ft_strdup(token);
	(*args_index)++;
}

void	handle_cmd_and_args(int cmd_idx, char *token, int *args_index)
{
	if (g_data.cur.cmd_list[cmd_idx]->cmd == NULL)
		handle_cmd(cmd_idx, token, args_index);
	else
		handle_args(cmd_idx, token, args_index);
}
