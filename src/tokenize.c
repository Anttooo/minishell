/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:09:34 by oanttoor          #+#    #+#             */
/*   Updated: 2022/10/24 16:09:35 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data g_data;

static int	count_tokens(char const *s, char c);
static void	write_token(char *dst, char *src, int index, int token_len);
static int	check_token_len(int	*x, char const *s, char c);
static int	write_tokens(char const *s, char c, int token_count);

int tokenize_input(void)
{
	int		token_count;

  // Count strings counts the number of tokens
	token_count = count_tokens(g_data.cur.raw, ' ');
  // malloc space for the token structs
	g_data.cur.tokens = (t_token **)malloc((token_count + 1) * sizeof(t_token *));
	if (g_data.cur.tokens == NULL)
		return (1);
	if (write_tokens(g_data.cur.raw, ' ', token_count) == 0)
		return (1);
	return (0);
}

// this part works correctly atm
static int	count_tokens(char const *s, char c)
{
	int	i;
	int	token_count;
  char  skip_char;

	i = 0;
	token_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			token_count++;
      // if there is a single or double quote, skip until the same character is seen again
      if(s[i] == '\"' || s[i] == '\'')
      {
        skip_char = s[i];
        i++;
        while(s[i] != skip_char && s[i] != '\0')
          i++;
      }
      ft_printf("Char we're at: %c\n", s[i]);
      // continue as usual with split
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
  ft_printf("Number of tokens from tokenize_input: %d \n", token_count);
	return (token_count);
}

static int	write_tokens(char const *s, char c, int token_count)
{
	int		token_len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (i < token_count)
	{
		token_len = check_token_len(&x, s, c);
    g_data.cur.tokens[i] = (t_token *)malloc(sizeof(t_token));
	  g_data.cur.tokens[i]->token = (char *)malloc((token_len + 1) * sizeof(char));
    g_data.cur.tokens[i]->type = (char *)malloc(50 * sizeof(char)); // malloc space for the type of token
		if (g_data.cur.tokens[i]->token == NULL)
		{
			i = 0;
			while (g_data.cur.tokens[i]->token)
			{
				free(g_data.cur.tokens[i]->token);
				i++;
			}
			free (g_data.cur.tokens);
			return (0);
		}
		write_token(g_data.cur.tokens[i]->token, (char *)s, x, token_len);
		i++;
	}
	return (1);
}

static int	check_token_len(int	*x, char const *s, char c)
{
	int	i;
	int	token_len;
  char  skip_char;

	i = *x;
	token_len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
    // if there is a single or double quote, skip until the same character is seen again
    if(s[i] == '\"' || s[i] == '\'')
    {
      skip_char = s[i];
      ft_printf("Skip char = %c, at index: %d\n", s[i], i);
      i++;
      while(s[i] != skip_char && s[i] != '\0')
      {
        i++;
        token_len++;
      }
      i++;
      token_len++;
    }
    else
    {
      token_len++;
      i++;
    }
	}
  ft_printf("leaving the while loop after char: %c, index: %d\n", s[i - 1], i);
	*x = i;
  ft_printf("token len from tokenize input: %d\n", token_len);
	return (token_len);
}

static void	write_token(char *dst, char *src, int index, int token_len)
{
	int		i;
	int		src_index;
	char	*ptr;

	ptr = src;
	src_index = index - token_len;
  ft_printf("First char to copy: %c\n", *(ptr + src_index));
	i = 0;
	while (i < token_len)
	{
		if (*(ptr + src_index) != '\'' && *(ptr + src_index) != '\"')
      *(dst + i) = *(ptr + src_index);
		i++;
		src_index++;
	}
	*(dst + i) = '\0';
  ft_printf("Token: %s\n", dst);
}
