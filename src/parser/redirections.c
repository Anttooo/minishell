/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 18:08:16 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/debug.h"

extern t_data	g_data;

/*
	Redirections can only accept certain tokens as arguments 
	and an invalid is a syntax error.
*/
int	is_valid_arg_for_redirection(char *token)
{
	if (ft_strncmp("|", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp("<", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp(">", token, ft_strlen(token)) == 0)
		return (0);
	return (1);
}

int	handle_input_redirection(int cmd_idx, char *token, int *mode)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		g_data.cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	g_data.cur.cmd_list[cmd_idx]->input = ft_strdup(token);
	*mode = DEFAULT_MODE;
	return (0);
}

int	handle_output_redirection(int cmd_idx, char *token, int *mode)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		g_data.cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	g_data.cur.cmd_list[cmd_idx]->output = ft_strdup(token);
	if (*mode == OUTPUT_REDIR_APPEND)
		g_data.cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
	else if (*mode == OUTPUT_REDIR_OVERWRITE)
		g_data.cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
	*mode = DEFAULT_MODE;
	return (0);
}
