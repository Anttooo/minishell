/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 10:27:04 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/tokenizer.h"

extern t_data	g_data;

// Evaluates a single character
int	evaluate_char(char c, int *mode, int *i)
{
	char	next_c;

	next_c = g_data.cur.raw[*i + 1];
	if (is_terminating_char(c, mode) == true)
		store_token();
	if (is_edge_case(c, next_c, mode, i) == 1)
		return (0);
	else
	{
		if (is_mode_changing_char(c, mode) || is_trigger_char(c, mode))
			return (1);
		if (is_stored_char(c, mode))
			add_char_to_buffer(g_data.cur.raw[*i]);
	}
	return (0);
}

// Checks if character terminates a token
int	is_terminating_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '\t'
			|| c == '|'
			|| c == '<' || c == '>'
			|| c == '\n')
			return (true);
	}
	return (false);
}

// Checks if character should be stored
int	is_stored_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '>'
			|| c == '<' || c == '\t'
			|| c == '\n' || c == '\''
			|| c == '\"' || c == '$')
			return (false);
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
			return (false);
	}
	return (true);
}

// Checks if character changes mode
int	is_mode_changing_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == '\'')
		{
			*mode = SINGLE_QUOTES_MODE;
			return (true);
		}
		if (c == '\"')
		{
			*mode = DOUBLE_QUOTES_MODE;
			return (true);
		}
	}
	else if (*mode == DOUBLE_QUOTES_MODE && c == '\"')
	{
		*mode = DEFAULT_MODE;
		if (g_data.cur.token_buffer.len == 0)
			store_empty_token();
		return (true);
	}
	else if (*mode == SINGLE_QUOTES_MODE && c == '\'')
	{
		*mode = DEFAULT_MODE;
		if (g_data.cur.token_buffer.len == 0)
			store_empty_token();
		return (true);
	}
	return (false);
}

// Checks if character triggers expansion
int	is_trigger_char(char c, int	*mode)
{
	if (*mode == DEFAULT_MODE || *mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
		{
			*mode += 10;
			return (true);
		}
	}
	return (false);
}
