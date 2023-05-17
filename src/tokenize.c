/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:09:34 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/17 16:56:33 by joonasmykka      ###   ########.fr       */
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
	// At this point check if the buffer includes only "|" or any redirections (<, >, >>)
	token->token = ft_strdup(buffer);
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
	printf("checking terminating character \n");
	if (*mode > 10)
	{
		if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|' || c == '\"' || c == '$' || c == '\n' || c == '\0')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}	
	}
	if (*mode == DEFAULT_MODE)
	{
		if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"' || c == '$' || c == '\n')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}
	}
	if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (true);
		}
	}
	if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
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
			printf("Mode changed to single quotes.\n");
			*mode = SINGLE_QUOTES_MODE;
			return (true);
		}
		if (c == '\"')
		{
			printf("Mode changed to double quotes.\n");
			*mode = DOUBLE_QUOTES_MODE;
			return (true);
		}
	}
	else if (*mode == DOUBLE_QUOTES_MODE)
	{
		if (c == '\"')
		{
			printf("Mode changed to default.\n");
			*mode = DEFAULT_MODE;
			return (true);
		}
	}
	else if (*mode == SINGLE_QUOTES_MODE)
	{
		if (c == '\'')
		{
			printf("Mode changed to default.\n");
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
			printf("In mode %d this character triggers expansion.\n", *mode);
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
    if (c == ' ' || c == '\t' || c == '\n' || c =='\'' || c == '\"' || c == '$')
    {
      printf("In mode %d this character is not stored in buffer\n", *mode);
      return (false);
    }
  }
  if (*mode == DOUBLE_QUOTES_MODE)
  {
    if (c == '$')
    {
      printf("In mode %d this character is not stored in buffer\n", *mode);
      return (false);
    }
  }
  return (true);
}

// Evaluates character
int evaluate_char(char	c, int *mode, int i) {
	if (is_terminating_char(c, mode))
		store_token();
  
	if (is_stored_char(c, mode))
		add_char_to_buffer(g_data.cur.raw[i]);
  
	if (is_mode_changing_char(c, mode) || is_trigger_char(c, mode))
		return 1;
  
	return 0;
}















// #include "../include/command.h"
// #include "../include/minishell.h"

// extern t_data g_data;

// char	*temp_env_var(char *str)
// {
// 	int		word_len;
// 	char	*var;
// 	int		idx;
// 	int		len;

// 	idx = -1;
// 	len = ft_strlen(str);
// 	while(g_data.env.vars[++idx] != NULL)
// 	{
// 		if (ft_strncmp(g_data.env.vars[idx], str, len) == 0)
// 			break;
// 	}
// 	word_len = ft_strlen( g_data.env.vars[idx]) - len - 1;
// 	var = malloc((word_len + 1) * sizeof(char));
// 	if (!var)
// 		return (NULL);
// 	ft_memcpy(var, &g_data.env.vars[idx][len + 1], word_len);
// 	var[word_len] = '\0';
// 	return (var);
// }

// // wrapper for vec_push to buffer
// void  add_char_to_buffer(char c)
// {
//   vec_push(&g_data.cur.token_buffer, (void *)&c);
// 	// If the char pushed to buffer is a character that should always be "alone", store current token
// 	if (c == '|')
// 		store_token();
// }

// void  empty_and_init_buffer(void)
// {
//   // TODO: add error handling
//   vec_free(&g_data.cur.token_buffer);
//   vec_new(&g_data.cur.token_buffer, 0 , sizeof(char));
// }

// // TODO: the tokens allocated here do not get freed anywhere yet
// void  store_current_token(void)
// {
// 	char	*buffer;
// 	t_token	*token;
// 	char	null_char;

// 	null_char = '\0';
// 	add_char_to_buffer(null_char);
// 	token = (t_token *)malloc(sizeof(t_token));
// 	buffer = (char *)vec_get(&g_data.cur.token_buffer, 0);
// 	debug_print_string(buffer, __func__);
// 	token->token = ft_strdup(buffer);
// 	// token->type = ft_strdup(buffer);
// 	// printf("in store current token: token->type: %s\n", token->type);
// 	vec_push(&g_data.cur.vec_tokens, token);
// }

// void  store_token(void)
// {
//   	if (g_data.cur.token_buffer.len != 0)
//   	{
//   		store_current_token();
//   		empty_and_init_buffer();
//   	}
// }

// /*
//   TOKENIZATION MODES

//   1 - default
//   2 - double quotes
//   3 - single quotes

// */
// int	tokenize_input(void)
// {
// 	vec_new(&g_data.cur.vec_tokens, 0, sizeof(t_token*));
//   // buffer vec
//   vec_new(&g_data.cur.token_buffer, 0, sizeof(char));
//   // error handling is needed here
// 	int	i;
// 	int	mode;

// 	mode = DEFAULT_MODE;
// 	i = 0;
// 	// If the char is whitespace, skip until there's something else
// 	if (g_data.cur.raw[i] == ' ' || g_data.cur.raw[i] == '\t')
// 		i++;
//   // before starting to evaluate the characters, a buffer should be created
//     // Create a buffer
// 	// while there are characters to look at, go through each of them one by one
// 	while(g_data.cur.raw[i] != '\0')
// 	{
// 		printf("\nChar is: %c\n", g_data.cur.raw[i]);
// 		evaluate_char(g_data.cur.raw[i], &mode, i);
// 			// somehow act based on the evaluation of the char, also depending on the mode we're in
// 		// If the token is terminated, store the buffer
// 			// store token from buffer
// 		// After we've evaluated the character, move to next one
// 		if (mode > 10) 
// 		{
// 			int j = i + 1;
// 			// get the rest of the search term after $
// 			while (is_terminating_char(g_data.cur.raw[j], &mode) == false)
// 			{
// 				j++;
// 			}
// 			printf("i: %d j: %d \n", i, j);
// 			// Update i so that the search term is skipped after the expansion
// 			char *env_var = ft_substr(g_data.cur.raw, (i + 1), (j - 1) - i);
// 			i = j - 1;
// 			// Pass that to get_env function (return char *)
// 			// Get the value back from get_env
// 			char *expanded_value = temp_env_var(env_var);
// 			// Throw that value in buffer using a loop
// 			j = 0;
// 			if (expanded_value)
// 			{
// 				while (expanded_value[j] != '\0')
// 				{
// 					add_char_to_buffer(expanded_value[j]);
// 					j++;
// 				}
// 			}
// 			// Turn off expansion mode and continue evaluating chars as usual
// 			mode -= 10;
// 		}
// 		i++;
// 	}
//   store_token();
// 	return (0);
// }

// int	is_terminating_char(char c, int *mode)
// {
// 	printf("checking terminating character \n");
// 	if (*mode > 10)
// 	{
// 		if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|' || c == '\"' || c == '$' || c == '\n' || c == '\0')
// 		{
// 			printf("In mode %d this character terminates a token.\n", *mode);
// 			return (true);
// 		}	
// 	}
// 	if (*mode == DEFAULT_MODE)
// 	{
// 		if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"' || c == '$' || c == '\n')
// 		{
// 			printf("In mode %d this character terminates a token.\n", *mode);
// 			return (true);
// 		}
// 	}
// 	if (*mode == DOUBLE_QUOTES_MODE)
// 	{
// 		if (c == '\"')
// 		{
// 			printf("In mode %d this character terminates a token.\n", *mode);
// 			return (true);
// 		}
// 	}
// 	if (*mode == SINGLE_QUOTES_MODE)
// 	{
// 		if (c == '\'')
// 		{
// 			printf("In mode %d this character terminates a token.\n", *mode);
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// int	is_mode_changing_char(char c, int *mode)
// {
// 	if (*mode == DEFAULT_MODE)
// 	{
// 		if (c == '\'')
// 		{
// 			printf("Mode changed to single quotes.\n");
// 			*mode = SINGLE_QUOTES_MODE;
// 			return (true);
// 		}
// 		if (c == '\"')
// 		{
// 			printf("Mode changed to double quotes.\n");
// 			*mode = DOUBLE_QUOTES_MODE;
// 			return (true);
// 		}
// 	}
// 	else if (*mode == DOUBLE_QUOTES_MODE)
// 	{
// 		if (c == '\"')
// 		{
// 			printf("Mode changed to default.\n");
// 			*mode = DEFAULT_MODE;
// 			return (true);
// 		}
// 	}
// 	else if (*mode == SINGLE_QUOTES_MODE)
// 	{
// 		if (c == '\'')
// 		{
// 			printf("Mode changed to default.\n");
// 			*mode = DEFAULT_MODE;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// int	is_trigger_char(char c, int	*mode)
// {
// 	if (*mode == DEFAULT_MODE || *mode == DOUBLE_QUOTES_MODE)
// 	{
// 		if (c == '$')
// 		{
// 			printf("In mode %d this character triggers expansion.\n", *mode);
// 			*mode += 10;
// 			// The action cuold be triggered here but not sure how that will happen
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

// int is_stored_char(char c, int *mode)
// {
//   if (*mode == DEFAULT_MODE)
//   {
//     if (c == ' ' || c == '\t' || c == '\n' || c =='\'' || c == '\"' || c == '$')
//     {
//       printf("In mode %d this character is not stored in buffer\n", *mode);
//       return (false);
//     }
//   }
//   if (*mode == DOUBLE_QUOTES_MODE)
//   {
//     if (c == '$')
//     {
//       printf("In mode %d this character is not stored in buffer\n", *mode);
//       return (false);
//     }
//   }
//   return (true);
// }

// int	evaluate_char(char	c, int *mode, int i)
// {
// 	if (is_terminating_char(c, mode) == true)
// 	{
// 		printf("-> Terminate the previous token\n");
// 		store_token();
// 	}
//   if (is_stored_char(c, mode) == true)
//   {
//     // printf("-> store to buffer\n");
//     add_char_to_buffer(g_data.cur.raw[i]);
//   }
// 	if (is_mode_changing_char(c, mode) != false)
// 	{
// 		printf("It's now: %d\n", *mode);
// 	}
// 	if (is_trigger_char(c, mode) == true)
// 	{
// 		printf("some action should be triggered\n");
// 	}
//   else
//   {
//     printf("-> Skip the char\n");
//   }
// 	return (1);
// }
