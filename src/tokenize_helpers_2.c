/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/24 16:44:10 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;
// Add a character to the buffer and store the token if necessary
void	add_char_to_buffer(char c) 
{
	vec_push(&g_data.cur.token_buffer, (void *)&c);
}

// Clear and initialize the buffer
void	clear_and_init_buffer(void)
{
	vec_free(&g_data.cur.token_buffer);
	vec_new(&g_data.cur.token_buffer, 0 , sizeof(char));
}

// Store token if buffer is not empty
void	store_token(void)
{
	if (g_data.cur.token_buffer.len != 0) {
		store_current_token();
		clear_and_init_buffer();
	}
}

// Store token if buffer is not empty
void	store_token_within_quotes(void)
{
	if (g_data.cur.token_buffer.len != 0) {
		ft_printf("test 2\n");
		store_current_token_within_quotes();
		clear_and_init_buffer();
	}
}

// Store the current token
void	store_current_token_within_quotes(void)
{
	t_token *token;

	ft_printf("test 3\n");
	add_char_to_buffer('\0');
	token = (t_token *)malloc(sizeof(t_token));
	token->token = ft_strdup((char *)vec_get(&g_data.cur.token_buffer, 0));
	token->type = WITHIN_QUOTES;
	debug_print_string(token->token, __func__);
	ft_printf("Type: %d\n", token->type);
	vec_push(&g_data.cur.vec_tokens, token);
}

// Checks if character triggers expansion
int is_trigger_char(char c, int	*mode)
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

// Checks if character should be stored
int is_stored_char(char c, int *mode) 
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '\t' || c == '\n' || c =='\'' || c == '\"' || c == '$' )
			return (false);
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
			return (false);
	}
	return (true);
}