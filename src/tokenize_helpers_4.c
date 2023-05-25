/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 15:27:19 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;

int	needs_blanc(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		printf("Creating planco token \n");
		if (c == ' ')
		{
			add_char_to_buffer(c);
			store_token();
		}
	}
}

// Checks if character terminates a token
int	is_terminating_char(char c, char next_c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '\t' || c == '|' || c == '\'' || c == '<' || c == '>' || c == '\"' || c == '$' || c == '\n')
			return (true);
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
			return (true);
	}
	if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
			return (true);
	}
	return (false);
}

// Check if the character is a letter or underscore
int is_valid_first_character(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') 
        return 1;
    return 0;
}

// Check if the character is a letter, digit, or underscore
int is_valid_subsequent_character(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
        return 1;
    return 0;
}

// Handles the expansion mode
// Turn off expansion mode and continue evaluating chars as usual
// The length of the env_var is checked to handle special case where $ is not followed by anything
void	handle_expansion_mode(int *mode, int *i)
{
	int		j;
	char	*expanded_value;
	char	*env_var;

	j = *i + 1;
	if (is_valid_first_character(g_data.cur.raw[j]))
		j++;
	while (is_valid_subsequent_character(g_data.cur.raw[j]))
		j++;
	env_var = ft_substr(g_data.cur.raw, (*i + 1), (j - 1) - *i);
	if (ft_strlen(env_var) > 0)
	{
		*i = j - 1;
		expanded_value = fetch_env_var(env_var);
		if (expanded_value)
		{
			j = 0;
			while (expanded_value[j] != '\0')
			{
				printf("Adding char to buffer: %c\n", expanded_value[j]);
				add_char_to_buffer(expanded_value[j]);
				j++;
			}
		}
	}
	else
		add_char_to_buffer('$');
	free(env_var);
	*mode -= 10;
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
	else if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
		{
			*mode = DEFAULT_MODE;
			return (true);
		}
	}
	else if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
		{
			*mode = DEFAULT_MODE;
			return (true);
		}
	}
	return (false);
}
