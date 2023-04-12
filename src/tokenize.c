/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:09:34 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/12 17:31:23 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data g_data;

int	evaluate_char(char	c, int *mode);

/*
Modes:
1 - default
2 - double quotes
3 - single quotes
*/
int	tokenize_input(void)
{
	vec_new(&g_data.cur.vec_tokens, 0, sizeof(t_token*));
	int	i;
	int	mode;

	mode = 1;
	i = 0;
	// If the char is whitespace, skip until there's something else
	if (g_data.cur.raw[i] == ' ' || g_data.cur.raw[i] == '	')
		i++;
	// while there are characters to look at
	while(g_data.cur.raw[i] != '\0')
	{
		printf("Char is: %c\n", g_data.cur.raw[i]);
		// Otherwise, evaluate the character
		evaluate_char(g_data.cur.raw[i], &mode);
			// somehow act based on the evaluation of the char, also depending on the mode we're in
		// If the token is terminated, store the buffer
			// store token from buffer
		// After we've evaluated the character, move to next one
		i++;
	}

	t_token	*token;
	t_token	*token2;


	token = (t_token*)malloc(sizeof(t_token));
	token->token = (char *)malloc(100 * sizeof(char));
	token->token = "Hello";
	token->type = (char *)malloc(50 * sizeof(char));
	token->type = "type";

	vec_push(&g_data.cur.vec_tokens, token);

	token2 = (t_token*)malloc(sizeof(t_token));
	token2->token = (char *)malloc(50 * sizeof(char));
	token2->token = "Hello2";
	token2->type = (char *)malloc(50 * sizeof(char));
	token2->type = "type2";
	vec_push(&g_data.cur.vec_tokens, token2);
	return (0);
}

int	is_terminating_char(char c, int *mode)
{
	if (*mode == 1)
	{
		if (c == ' ' || c == '	' || c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"' || c == '$')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (1);
		}
	}
	if (*mode == 2)
	{
		if (c == '\"')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (1);
		}
	}
	if (*mode == 3)
	{
		if (c == '\'')
		{
			printf("In mode %d this character terminates a token.\n", *mode);
			return (1);
		}
	}
	return (0);
}

int	is_mode_changing_char(char c, int *mode)
{
	if (*mode == 1)
	{
		if (c == '\'')
		{
			printf("Mode changed to single quotes.\n");
			*mode = 3;
		}
		if (c == '\"')
		{
			printf("Mode changed to double quotes.\n");
			*mode = 2;
		}
	}
	else if (*mode == 2)
	{
		if (c == '\"')
		{
			printf("Mode changed to default.\n");
			*mode = 1;
		}
	}
	else if (*mode == 3)
	{
		if (c == '\'')
		{
			printf("Mode changed to default.\n");
			*mode = 1;
		}
	}
	return (0);
}

int	is_trigger_char(char c, int	*mode)
{
	if (*mode == 1)
	{
		if (c == '$')
		{
			printf("In mode %d this character triggers expansion.\n", *mode);
			return (1);
		}
	}
	return (0);
}

int	evaluate_char(char	c, int *mode)
{
	int	add_to_buffer;

	add_to_buffer = 1;
	if (is_terminating_char(c, mode) == 1)
	{
		printf("The previous token is terminated here.\n");
		add_to_buffer = 0;
	}
	if (is_mode_changing_char(c, mode) != 0)
	{
		printf("It's now: %d\n", *mode);
		add_to_buffer = 0;
	}
	if (is_trigger_char(c, mode) == 1)
	{
		printf("some action should be triggered\n");
		add_to_buffer = 0;
	}
	return (1);
}

// static int	count_tokens(char const *s);
// static void	write_token(char *dst, char *src, int index, int token_len);
// static int	check_token_len(int	*x, char const *s);
// static int	write_tokens(char const *s, int token_count);

// int tokenize_input(void)
// {
// 	int		token_count;

//   	// Count strings counts the number of tokens
// 	token_count = count_tokens(g_data.cur.raw);
//   	// malloc space for the token structs
// 	g_data.cur.tokens = (t_token **)malloc((token_count + 1) * sizeof(t_token *));
// 	if (g_data.cur.tokens == NULL)
// 		return (1);
// 	if (write_tokens(g_data.cur.raw, token_count) == 0)
// 		return (1);
// 	g_data.cur.tokens[token_count] = NULL;
// 	return (0);
// }

// // this part works correctly atm
// static int	count_tokens(char const *s)
// {
// 	int		i;
// 	int		token_count;
//   	char	skip_char;

// 	i = 0;
// 	token_count = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == ' ')
// 			i++;
// 		else
// 		{
// 			token_count++;
//       // if there is a single or double quote, skip until the same character is seen again
//       if(s[i] == '\"' || s[i] == '\'')
//       {
//         skip_char = s[i];
//         i++;
//         while(s[i] != skip_char && s[i] != '\0')
//           i++;
//       }
//       // continue as usual with split
// 			while (s[i] != ' ' && s[i] != '\0')
// 				i++;
// 		}
// 	}
// 	return (token_count);
// }

// static int	write_tokens(char const *s, int token_count)
// {
// 	int		token_len;
// 	int		i;
// 	int		x;

// 	i = 0;
// 	x = 0;
// 	while (i < token_count)
// 	{
// 		// I could also get the start and end index here
// 		token_len = check_token_len(&x, s);
// 		g_data.cur.tokens[i] = (t_token *)malloc(sizeof(t_token));
// 		g_data.cur.tokens[i]->token = (char *)malloc((token_len + 1) * sizeof(char));
// 		g_data.cur.tokens[i]->type = (char *)malloc(50 * sizeof(char)); // malloc space for the type of token
// 		if (g_data.cur.tokens[i]->token == NULL)
// 		{
// 			i = 0;
// 			while (g_data.cur.tokens[i]->token)
// 			{
// 				free(g_data.cur.tokens[i]->token);
// 				i++;
// 			}
// 			free (g_data.cur.tokens);
// 			return (0);
// 		}
// 		// This could be store token, which includes giving it type and writing the token
// 		write_token(g_data.cur.tokens[i]->token, (char *)s, x, token_len);
// 		i++;
// 	}
// 	return (1);
// }


// // I would want this function to return the actual length of the token
// static int	check_token_len(int	*x, char const *s)
// {
// 	int		i;
// 	int		token_len;
//   	char	skip_char;

// 	i = *x;
// 	token_len = 0;
// 	// If there are spaces in the beginning, skip them.
// 	while (s[i] == ' ')
// 		i++;
// 	while (s[i] != ' ' && s[i] != '\0')
// 	{
//     	// if there is a single or double quote, skip until the same character is seen again
// 		if(s[i] == '\"' || s[i] == '\'')
// 		{
// 			skip_char = s[i];
// 			i++;
// 			token_len++;
// 			// TODO: make it return an error if there isn't a corresponding skip_char
// 			while(s[i] != skip_char && s[i] != '\0')
// 			{
// 				i++;
// 				token_len++;
// 			}
// 			i++;
// 			token_len++;
// 		}
// 		else
// 		{
// 			token_len++;
// 			i++;
// 		}
// 	}
// 	*x = i;
// 	printf("token len: %d\n", token_len);
// 	return (token_len);
// }

// // I would want this function not to depend on the token_len on getting the right
// // string into the token
// static void	write_token(char *dst, char *src, int index, int token_len)
// {
// 	int		i;
// 	int		src_index;
// 	char	*ptr;

// 	ptr = src;
// 	src_index = index - token_len;
// 	i = 0;
// 	while (i < token_len)
// 	{
		
// 		if (*(ptr + src_index) != '\'' && *(ptr + src_index) != '\"')
// 		{
// 			*(dst + i) = *(ptr + src_index);
// 			i++;
// 		}
// 		src_index++;
// 	}
// 	*(dst + i) = '\0';
// }
