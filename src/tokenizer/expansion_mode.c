/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:41:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 15:10:08 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/tokenizer.h"

extern t_data	g_data;

// Expansion mode helper
static void	handle_expanded_value(char *env_var)
{
	char	*expanded_value;
	int		j;

	expanded_value = fetch_env_var(env_var);
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

// Handles expansion mode
void	handle_expansion_mode(int *mode, int *i)
{
	char	*env_var;
	int		j;
	int		k;
	char	*exit_status;

	j = *i + 1;
	k = 0;
	if (g_data.cur.raw[j] == '?' && (g_data.cur.raw[j + 1] == ' ' || g_data.cur.raw[j + 1] == '\0'))
	{
		exit_status = ft_itoa(g_data.env.exit_status);
		while (exit_status[k] != '\0')
		{
			add_char_to_buffer(exit_status[k]);
			k++;
		}
		free(exit_status);
		// if (g_data.cur.raw[j + 1] != '\0')
		*i = j + 1;
		*mode -= 10;
	}

	if (is_valid_first_character(g_data.cur.raw[j]))
		j++;
	while (is_valid_subsequent_character(g_data.cur.raw[j]))
		j++;
	env_var = ft_substr(g_data.cur.raw, (*i + 1), (j - 1) - *i);
	if (ft_strlen(env_var) > 0)
	{
		*i = j - 1;
		handle_expanded_value(env_var);
	}
	else if (g_data.cur.raw[*i + 1] == ' ' || g_data.cur.raw[*i + 1] == '\0')
		add_char_to_buffer('$');
	*mode -= 10;
}

// Check if the character is a letter or underscore
int	is_valid_first_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '=')
		return (1);
	return (0);
}

// Check if the character is a letter, digit, or underscore
int	is_valid_subsequent_character(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

// Fetch environment variable
char	*fetch_env_var(char *str)
{
	int		idx;
	int		len;
	char	*needle;
	int		word_len;
	char	*var;

	idx = -1;
	needle = ft_strjoin(str, "=");
	len = ft_strlen(needle);
	free(str);
	while (g_data.env.vars[++idx] != NULL)
	{
		if (ft_strncmp(g_data.env.vars[idx], needle, len) == 0)
			break ;
	}
	if (g_data.env.vars[idx] == NULL)
		return (NULL);
	word_len = ft_strlen(g_data.env.vars[idx]) - len;
	var = malloc((word_len + 1) * sizeof(char));
	if (!var)
	{
		free(needle);
		return (NULL);
	}
	ft_strlcpy(var, &g_data.env.vars[idx][len], word_len + 1);
	free(needle);
	return (var);
}
