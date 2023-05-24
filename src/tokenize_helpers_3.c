/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/24 16:14:26 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;

// Store the current token
void	store_current_token() {
	t_token *token;
	
	add_char_to_buffer('\0');
	token = (t_token *)malloc(sizeof(t_token));
	token->token = ft_strdup((char *)vec_get(&g_data.cur.token_buffer, 0));
	token->type = DEFAULT;
	debug_print_string(token->token, __func__);
	vec_push(&g_data.cur.vec_tokens, token);
}


// Fetch environment variable
char	*fetch_env_var(char *str) {
	int idx;
	int len;
	
	idx = 0;
	len = ft_strlen(str);
	while(g_data.env.vars[idx] != NULL) {
		if (ft_strncmp(g_data.env.vars[idx], str, len) == 0)
			break;
		idx++;
	}
	int word_len = ft_strlen(g_data.env.vars[idx]) - len - 1;
	char *var = malloc((word_len + 1) * sizeof(char));
	if (!var)
		return (NULL);
	ft_memcpy(var, &g_data.env.vars[idx][len + 1], word_len);
	var[word_len] = '\0';
	return (var);
}

// To handle double greater than ">>" we add both to buffer, store the buffer, and skip to next character
void	handle_double_greater_than(int *i)
{
	add_char_to_buffer('>');
	add_char_to_buffer('>');
	*i = *i + 1;
}
