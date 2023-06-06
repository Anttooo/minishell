/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:41:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 19:07:18 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/tokenizer.h"

extern t_data	g_data;

// env_var_idx = index in the value e.g. 123 in abc=123
void	handle_exit_status_expansion(int *mode, int *input_idx)
{
	int		env_var_idx;
	char	*exit_status;

	env_var_idx = 0;
	exit_status = ft_itoa(g_data.env.exit_status);
	malloc_error_check(exit_status);
	while (exit_status[env_var_idx] != '\0')
	{
		add_char_to_buffer(exit_status[env_var_idx]);
		env_var_idx++;
	}
	free(exit_status);
	(*input_idx)++;
	*mode -= 10;
}

char	*get_identifier(int *input_idx, int *identifier_idx)
{
	char	*identifier;

	if (is_valid_first_character(g_data.cur.raw[*identifier_idx]))
		(*identifier_idx)++;
	while (is_valid_subsequent_character(g_data.cur.raw[*identifier_idx]))
		(*identifier_idx)++;
	identifier = ft_substr(g_data.cur.raw, (*input_idx + 1), \
						(*identifier_idx - 1) - *input_idx);
	return (identifier);
}

static void	handle_expanded_value(char *identifier)
{
	char	*expanded_value;
	int		j;

	expanded_value = fetch_env_var(identifier);
	if (expanded_value)
	{
		j = 0;
		while (expanded_value[j] != '\0')
		{
			add_char_to_buffer(expanded_value[j]);
			j++;
		}
		free(expanded_value);
	}
}

void	handle_env_var_expansion(int *mode, int *input_idx, int identifier_idx)
{
	char	*identifier;

	identifier = get_identifier(input_idx, &identifier_idx);
	if (ft_strlen(identifier) > 0)
	{
		*input_idx = identifier_idx - 1;
		handle_expanded_value(identifier);
	}
	else if (is_terminating_char(g_data.cur.raw[*input_idx + 1], mode))
		add_char_to_buffer('$');
	else if (*mode == DOUBLE_QUOTES_MODE + 10)
		add_char_to_buffer('$');
	*mode -= 10;
}

// Handles expansion mode
// input_idx = index in the raw input
// identifier_idx = index in the identifier, e.g. abc in abc=123
void	handle_expansion_mode(int *mode, int *input_idx)
{
	int		identifier_idx;

	identifier_idx = *input_idx + 1;
	if (is_exit_status_expansion(identifier_idx) == 1)
	{
		handle_exit_status_expansion(mode, input_idx);
	}
	else
	{
		handle_env_var_expansion(mode, input_idx, identifier_idx);
	}
}
