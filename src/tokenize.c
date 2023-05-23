/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:09:34 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/23 12:30:15 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data g_data;

// Fetch environment variable
char *fetch_env_var(char *str) {
	int idx = 0;
	int len = ft_strlen(str);

	while(g_data.env.vars[idx] != NULL) {
		if (ft_strncmp(g_data.env.vars[idx], str, len) == 0)
			break;
		idx++;
	}

	int word_len = ft_strlen(g_data.env.vars[idx]) - len - 1;
	char *var = malloc((word_len + 1) * sizeof(char));

	if (!var)
		return NULL;

	ft_memcpy(var, &g_data.env.vars[idx][len + 1], word_len);
	var[word_len] = '\0';
	return var;
}

// Add a character to the buffer and store the token if necessary
void add_char_to_buffer(char c) {
  // printf("Adding character to buffer: %d\n", c);
	vec_push(&g_data.cur.token_buffer, (void *)&c);
	if (c == '|')
		store_token();
}

// Clear and initialize the buffer
void clear_and_init_buffer() {
	vec_free(&g_data.cur.token_buffer);
	vec_new(&g_data.cur.token_buffer, 0 , sizeof(char));
}

// Store the current token
void store_current_token() {
	char null_char = '\0';
	add_char_to_buffer(null_char);
	
	t_token *token = (t_token *)malloc(sizeof(t_token));
	char *buffer = (char *)vec_get(&g_data.cur.token_buffer, 0);
	token->token = ft_strdup(buffer);
  // debug_print_string(token->token, __func__); // TODO: remove
	vec_push(&g_data.cur.vec_tokens, token);
}

// Store token if buffer is not empty
void store_token() {
	if (g_data.cur.token_buffer.len != 0) {
		store_current_token();
		clear_and_init_buffer();
	}
}

// Handles the expansion mode
void handle_expansion_mode(int *mode, int *i) {
	int j = *i + 1;
	// Continue until the character terminates a token
	while (!is_terminating_char(g_data.cur.raw[j], mode))
		j++;

	char *env_var = ft_substr(g_data.cur.raw, (*i + 1), (j - 1) - *i);
	*i = j - 1;

	char *expanded_value = fetch_env_var(env_var);
	if (expanded_value)
	{
		j = 0;
		while (expanded_value[j] != '\0')
		{
			add_char_to_buffer(expanded_value[j]);
			j++;
		}
	}

	// Turn off expansion mode and continue evaluating chars as usual
	*mode -= 10;
}

// Tokenize input
int tokenize_input() {
	vec_new(&g_data.cur.vec_tokens, 0, sizeof(t_token*));
	vec_new(&g_data.cur.token_buffer, 0, sizeof(char));

	int i = 0;
	int mode = DEFAULT_MODE;

	while(g_data.cur.raw[i] != '\0') {
		evaluate_char(g_data.cur.raw[i], &mode, i);
		if (mode > 10) 
			handle_expansion_mode(&mode, &i);
		i++;
	}
	store_token(); // stores the last token once the input string ends
	// Add types to tokens
	
	return 0;
}

// Checks if character terminates a token
int is_terminating_char(char c, int *mode) {
	// printf("checking terminating character \n");
	if (*mode > 10)
	{
		if (c == ' ' || c == '\t' || c == '|' || c == '\"' || c == '$' || c == '\n' || c == '\0')
		{
			// printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}	
	}
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '\t' || c == '|' || c == '\'' || c == '\"' || c == '$' || c == '\n')
		{
			// printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
		{
			// printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}
	}
	if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
		{
			// printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}
	}
	return (false);
}

// Checks if character changes mode
int is_mode_changing_char(char c, int *mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == '\'')
		{
			// printf("Mode changed to single quotes.\n");
			*mode = SINGLE_QUOTES_MODE;
			return (true);
		}
		if (c == '\"')
		{
			// printf("Mode changed to double quotes.\n");
			*mode = DOUBLE_QUOTES_MODE;
			return (true);
		}
	}
	else if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
		{
			// printf("Mode changed to default.\n");
			*mode = DEFAULT_MODE;
			return (true);
		}
	}
	else if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
		{
			// printf("Mode changed to default.\n");
			*mode = DEFAULT_MODE;
			return (true);
		}
	}
	return (false);
}


// Checks if character triggers expansion
int is_trigger_char(char c, int	*mode) {
	if (*mode == DEFAULT_MODE || *mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '$')
		{
			// printf("In mode %d this character triggers expansion.\n", *mode);
			*mode += 10;
			// The action cuold be triggered here but not sure how that will happen
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
    {
      // printf("In mode %d this character |%c| is not stored in buffer\n", *mode, c);
      return (false);
    }
  }
  if (*mode == DOUBLE_QUOTES_MODE)
  {
    if (c == '$')
    {
      // printf("In mode %d this character is not stored in buffer\n", *mode);
      return (false);
    }
  }
  return (true);
}

// Evaluates character
int evaluate_char(char	c, int *mode, int i) {
  // printf("Evaluating character: %c\n", c);
	if (is_terminating_char(c, mode))
		store_token();
  
	if (is_mode_changing_char(c, mode) || is_trigger_char(c, mode))
		return 1;

	if (is_stored_char(c, mode))
		add_char_to_buffer(g_data.cur.raw[i]);
  
  
	return 0;
}
