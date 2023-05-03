/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:09:34 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/03 10:27:53 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data g_data;

// wrapper for vec_push to buffer
void  add_char_to_buffer(char c)
{
  vec_push(&g_data.cur.token_buffer, (void *)&c);
}

void  empty_and_init_buffer(void)
{
  // TODO: add error handling
  vec_free(&g_data.cur.token_buffer);
  vec_new(&g_data.cur.token_buffer, 0 , sizeof(char));
}

// TODO: the tokens allocated here do not get freed anywhere yet
void  store_current_token(void)
{
	char	*buffer;
	t_token	*token;
	char	null_char;

	null_char = '\0';
	add_char_to_buffer(null_char);
	token = (t_token *)malloc(sizeof(t_token));
	buffer = (char *)vec_get(&g_data.cur.token_buffer, 0);
	// token->token = ft_strdup(buffer);
	token->type = ft_strdup(buffer);
	printf("in store current token: token->type: %s\n", token->type);
	vec_push(&g_data.cur.vec_tokens, token);
}

void  store_token(void)
{
  if (g_data.cur.token_buffer.len != 0)
  {
  	store_current_token();
  	empty_and_init_buffer();
  }
}

int	evaluate_char(char	c, int *mode, int i);

/*
  TOKENIZATION MODES

  1 - default
  2 - double quotes
  3 - single quotes

*/
int	tokenize_input(void)
{
	vec_new(&g_data.cur.vec_tokens, 0, sizeof(t_token*));
  // buffer vec
  vec_new(&g_data.cur.token_buffer, 0, sizeof(char));
  // error handling is needed here
	int	i;
	int	mode;

	mode = DEFAULT_MODE;
	i = 0;
	// If the char is whitespace, skip until there's something else
	if (g_data.cur.raw[i] == ' ' || g_data.cur.raw[i] == '\t')
		i++;
  // before starting to evaluate the characters, a buffer should be created
    // Create a buffer
	// while there are characters to look at, go through each of them one by one
	while(g_data.cur.raw[i] != '\0')
	{
		printf("\nChar is: %c\n", g_data.cur.raw[i]);
		evaluate_char(g_data.cur.raw[i], &mode, i);
			// somehow act based on the evaluation of the char, also depending on the mode we're in
		// If the token is terminated, store the buffer
			// store token from buffer
		// After we've evaluated the character, move to next one
		i++;
	}
  store_token();
	return (0);
}

int	is_terminating_char(char c, int *mode)
{
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

int	is_mode_changing_char(char c, int *mode)
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

int	is_trigger_char(char c, int	*mode)
{
	if (*mode == DEFAULT_MODE)
	{
		if (c == '$')
		{
			printf("In mode %d this character triggers expansion.\n", *mode);
			return (true);
		}
	}
	return (false);
}

int is_stored_char(char c, int *mode)
{
  if (*mode == DEFAULT_MODE)
  {
    if (c == ' ' || c == '\t' || c == '\n')
    {
      printf("In mode %d this character is not stored in buffer\n", *mode);
      return (false);
    }
  }
  return (true);
}

int	evaluate_char(char	c, int *mode, int i)
{
	if (is_terminating_char(c, mode) == true)
	{
		printf("-> Terminate the previous token\n");
		store_token();
	}
	if (is_mode_changing_char(c, mode) != false)
	{
		printf("It's now: %d\n", *mode);
	}
	if (is_trigger_char(c, mode) == true)
	{
		printf("some action should be triggered\n");
	}
  if (is_stored_char(c, mode) == true)
  {
    printf("-> store to buffer\n");
    add_char_to_buffer(g_data.cur.raw[i]);
  }
  else
  {
    printf("-> Skip the char\n");
  }
	return (1);
}
