/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/24 16:54:15 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data	g_data;

// Tokenize input
// stores the last token once the input string ends
int	tokenize_input(void)
{
	int	i;
	int	mode;

	i = 0;
	mode = DEFAULT_MODE;
	vec_new(&g_data.cur.vec_tokens, 0, sizeof(t_token *));
	vec_new(&g_data.cur.token_buffer, 0, sizeof(char));
	while (g_data.cur.raw[i] != '\0')
	{
		evaluate_char(g_data.cur.raw[i], &mode, &i);
		if (mode > 10)
			handle_expansion_mode(&mode, &i);
		i++;
	}
	store_token();
	return (0);
}

int	is_edge_case(char c, char next_c, int *mode, int *i)
{
	if ((*mode == SINGLE_QUOTES_MODE || *mode == DOUBLE_QUOTES_MODE))
	{
		ft_printf("Checking for edge cases\n");
		ft_printf("Char: %c, next: %c\n", c, next_c);
		if (c == '<' && (next_c == '\'' || next_c == '\"'))
		{
			add_char_within_quotes(c);
			return (0);
		}
		else if (c == '>' && next_c != '>' && (g_data.cur.raw[*i + 1] == '\'' || g_data.cur.raw[*i + 1] == '\"'))
		{
			add_char_within_quotes(c);
			return (0);
		}
		else if (c == '|' && (next_c == '\'' || next_c == '\"'))
		{
			ft_printf("Found pipe within quotes\n");
			add_char_within_quotes(c);
			return (0);
		}
		else if (c == '>' && next_c == '>' && (g_data.cur.raw[*i + 2] == '\'' || g_data.cur.raw[*i + 2] == '\"'))
		{
			add_double_greater_than_within_quotes(i);
			return (0);
		}
	}
	else if (*mode == DEFAULT_MODE && c == '|')
	{
		add_char_to_buffer(c);
		store_token();
	}
	else if (*mode == DEFAULT_MODE && is_double_greater_than(c, next_c))
	{
		handle_double_greater_than(i);
		store_token();
	}
	else if (*mode == DEFAULT_MODE && is_greater_than(c) && !is_greater_than(next_c))
	{
		add_char_to_buffer(c);
		store_token();
	}
	else if (*mode == DEFAULT_MODE && is_smaller_than(c) && !is_smaller_than(next_c))
	{
		add_char_to_buffer(c);
		store_token();
	}
	return (1);
}

// Evaluates a single character
int	evaluate_char(char c, int *mode, int *i)
{
	char	next_c;

	next_c = g_data.cur.raw[*i + 1];
	if (is_terminating_char(c, next_c, mode))
		store_token();
	if (is_edge_case(c, next_c, mode, i) == 0)
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
