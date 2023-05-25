/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 10:30:030 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;

// Store the current token
void	store_current_token(void) {
	char	*token;
	int		type;

	type = DEFAULT;
	add_char_to_buffer('\0');
	token = ft_strdup((char *)vec_get(&g_data.cur.token_buffer, 0));
	vec_push(&g_data.cur.tokens, &token); 
	char *test = *(char **)vec_get(&g_data.cur.tokens, 0);
	vec_push(&g_data.cur.types, &type);
}


// Fetch environment variable
char	*fetch_env_var(char *str) {
	int idx;
	int len;
	char *needle;
	
	idx = 0;
	needle = ft_strjoin(str, "=");
	len = ft_strlen(needle);
	debug_print_string(needle, __func__);
	free(str);
	while(g_data.env.vars[idx] != NULL) {
		debug_print_string(g_data.env.vars[idx], __func__);
		if (ft_strncmp(g_data.env.vars[idx],  needle, len) == 0)
			break;
		idx++;
	}
	int word_len = ft_strlen(g_data.env.vars[idx]) - len - 1;
	char *var = malloc((word_len + 1) * sizeof(char));
	if (!var)
		return (NULL);
	ft_memcpy(var, &g_data.env.vars[idx][len + 1], word_len);
	var[word_len] = '\0';
	debug_print_string(var, __func__);
	return (var);
}

// To handle double greater than ">>" we add both to buffer, store the buffer, and skip to next character
void	handle_double_greater_than(int *i)
{
	add_char_to_buffer('>');
	add_char_to_buffer('>');
	*i = *i + 1;
}
