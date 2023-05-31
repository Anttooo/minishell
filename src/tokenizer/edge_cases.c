/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:16:08 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 18:16:19 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;

int	handle_within_quotes(char c, char next_c, int *i)
{
	if (c == '<' && (next_c == '\'' || next_c == '\"'))
	{
		add_char_within_quotes(c);
		return (1);
	}
	else if (c == '>' && next_c != '>' && (g_data.cur.raw[*i + 1] == '\''
			|| g_data.cur.raw[*i + 1] == '\"'))
	{
		add_char_within_quotes(c);
		return (1);
	}
	else if (c == '|' && (next_c == '\'' || next_c == '\"'))
	{
		add_char_within_quotes(c);
		return (1);
	}
	else if (c == '>' && next_c == '>' && (g_data.cur.raw[*i + 2] == '\''
			|| g_data.cur.raw[*i + 2] == '\"'))
	{
		add_double_greater_than_within_quotes(i);
		return (1);
	}
	return (0);
}

int	handle_default_mode(char c, char next_c, int *i)
{
	if (c == '>' && next_c == '>')
	{
		handle_double_greater_than(i);
		store_token();
		return (1);
	}
	else if (c == '>' && next_c != '>')
	{
		add_char_to_buffer(c);
		store_token();
		return (1);
	}
	else if (c == '<')
	{
		add_char_to_buffer(c);
		store_token();
		return (1);
	}
	else if (c == '|')
	{
		add_char_to_buffer(c);
		store_token();
		return (1);
	}
	return (0);
}

int	is_edge_case(char c, char next_c, int *mode, int *i)
{
	if ((*mode == SINGLE_QUOTES_MODE || *mode == DOUBLE_QUOTES_MODE))
	{
		return (handle_within_quotes(c, next_c, i));
	}
	else if (*mode == DEFAULT_MODE)
	{
		return (handle_default_mode(c, next_c, i));
	}
	return (0);
}
