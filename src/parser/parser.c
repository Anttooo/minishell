/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/25 12:28:445 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/minishell.h"
#include "../../include/debug.h"

extern t_data	g_data;


// Parse input takes in a perfect list of tokens and creates perfect command structs that can be passed to execute
int	parse_commands(void)
{
	int cmd_idx;
	int token_idx;

	cmd_idx = 0;
	token_idx = 0;
	get_cmd_count();
	allocate_cmd_list();
	while (cmd_idx < g_data.cur.cmd_count) {
		parse_single_cmd(cmd_idx, &token_idx);
    	token_idx++;
		cmd_idx++;
	}
	return (0);
}

// get_token should return the entire token
t_token *get_token(int token_idx)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	t->token = *(char **)vec_get(&g_data.cur.tokens, token_idx);
	t->type = (int)vec_get(&g_data.cur.types, token_idx);
	return (t);
}

// Checks the token type and if it's within_quotes, does not even compare it
int	is_delim_token(int i)
{
	t_token *t;

	t = get_token(i);
	if (t->type == DEFAULT && ft_strncmp("|", t->token, ft_strlen(t->token)) == 0)
	{
		return (1);
	}
	return (0);
}

// Checks if the mode should be changed
// If the token type is something else than default, the token can not influence mode so checks are skipped
int  check_mode(t_token *t, int cmd_idx)
{
	ft_printf("Are we checking modes? type: %d\n", t->type);
	// if token->type = within quotes, return default mode
	if (t->type == DEFAULT)
	{
		if (ft_strncmp("<", t->token, ft_strlen(t->token)) == 0)
		{
			return (INPUT_REDIR);
		}
		if (ft_strncmp(">", t->token, ft_strlen(t->token)) == 0)
		{
			g_data.cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
			return (OUTPUT_REDIR_OVERWRITE);
		}
		if (ft_strncmp(">>", t->token, ft_strlen(t->token)) == 0)
		{
			g_data.cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
			return (OUTPUT_REDIR_APPEND);
		}	
	}
	return (DEFAULT_MODE);
}

void	parse_single_cmd(int cmd_idx, int *token_idx)
{
	t_token		*t;
	int			mode;
	int			args_index;

	args_index = 0;
	mode = DEFAULT_MODE;
	while (*token_idx < g_data.cur.tokens.len && is_delim_token(*token_idx) == 0) // token type influences delim_token
	{
		t = get_token(*token_idx);
		mode = check_mode(t, cmd_idx); // token type inlfluences this
		if (mode != DEFAULT_MODE) // if the token changes mode, we need the next token before going forward
		{
			*token_idx = *token_idx + 1;
			if (*token_idx < g_data.cur.tokens.len) {
				t = get_token(*token_idx);
			}
		}
		if (g_data.cur.cmd_list[cmd_idx]->cmd == NULL && mode == DEFAULT_MODE) // If cmd has not been defined for this cmd struct
		{
     	g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(t->token);
			g_data.cur.cmd_list[cmd_idx]->args = (char**)malloc(100*sizeof(char *));
			g_data.cur.cmd_list[cmd_idx]->args[args_index++] = ft_strdup(t->token);
		}
		else if (mode == DEFAULT_MODE) // fill args
		{
			g_data.cur.cmd_list[cmd_idx]->args[args_index++] = ft_strdup(t->token);
		}
		else if (mode == INPUT_REDIR)
		{
			// TODO: validate that the token is valid (e.g. < > | are not valid)
			printf("cmd_idx = %d and g_data.cur.input == NULL : %d\n", cmd_idx, g_data.cur.input == NULL);
			if (cmd_idx == 0)
				g_data.cur.input = ft_strdup(t->token);
			else
				g_data.cur.cmd_list[cmd_idx]->input = ft_strdup(t->token);
			mode = DEFAULT_MODE;
		}
		else if (mode == OUTPUT_REDIR_APPEND || mode == OUTPUT_REDIR_OVERWRITE)
		{
			if (cmd_idx == g_data.cur.cmd_count - 1)
			{
				g_data.cur.output = ft_strdup(t->token);
				if (mode == OUTPUT_REDIR_APPEND)
					g_data.cur.output_mode = APPEND_MODE;
				else if (mode == OUTPUT_REDIR_OVERWRITE)
					g_data.cur.output_mode = OVERWRITE_MODE;
			}
			else
				g_data.cur.cmd_list[cmd_idx]->output = ft_strdup(t->token);
			mode = DEFAULT_MODE;
		}
		*token_idx = *token_idx + 1;
		free(t);
	}
}
