/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 15:54:40 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern	t_data g_data;

// Store token if buffer is not empty
void	store_token(void)
{
	if (g_data.cur.token_buffer.len != 0) 
	{
		store_current_token();
		clear_and_init_buffer();
	}
}

// Store the current token
void	store_current_token(void)
{
	char	*token;
	int		type;

	type = DEFAULT;
	add_char_to_buffer('\0');
	token = ft_strdup((char *)vec_get(&g_data.cur.token_buffer, 0));
	vec_push(&g_data.cur.tokens, &token);
	vec_push(&g_data.cur.types, &type);
}

// Store token if buffer is not empty
void	store_token_within_quotes(void)
{
	if (g_data.cur.token_buffer.len != 0)
	{
		store_current_token_within_quotes();
		clear_and_init_buffer();
	}
}

// Store the current token
void	store_current_token_within_quotes(void)
{
	char	*token;
	int		type;

	type = WITHIN_QUOTES;
	add_char_to_buffer('\0');
	token = ft_strdup((char *)vec_get(&g_data.cur.token_buffer, 0));
	vec_push(&g_data.cur.tokens, &token);
	vec_push(&g_data.cur.types, &type);
}
