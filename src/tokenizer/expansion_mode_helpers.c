/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_mode_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:51:57 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 15:40:49 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"
#include "../../include/tokenizer.h"

extern t_data	g_data;

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
	malloc_error_check(var);
	ft_strlcpy(var, &g_data.env.vars[idx][len], word_len + 1);
	free(needle);
	return (var);
}

// Check if the character is a letter or underscore
int	is_valid_first_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
								|| c == '_' || c == '=')
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

int	is_exit_status_expansion(int j)
{
	if (g_data.cur.raw[j] == '?' && (g_data.cur.raw[j + 1] == ' ' \
								|| g_data.cur.raw[j + 1] == '\0'))
		return (1);
	else
		return (0);
}
