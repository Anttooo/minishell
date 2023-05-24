/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/24 10:33:16 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"
#include "../include/debug.h"

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

char* get_token(int token_idx)
{
	t_token	*t;

	t = (t_token *)vec_get(&g_data.cur.vec_tokens, token_idx);
	return (t->token);
}

int	is_delim_token(int i)
{
	char *token;

	token = get_token(i);
	if (ft_strncmp("|", token, ft_strlen(token)) == 0)
	{
		return (1);
	}
	return (0);
}

// Checks if the mode should be changed
int  check_mode(char* token, int cmd_idx)
{
  if (ft_strncmp("<", token, ft_strlen(token)) == 0)
  {
    return (INPUT_REDIR);
  }
  if (ft_strncmp(">", token, ft_strlen(token)) == 0)
  {
    g_data.cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
    return (OUTPUT_REDIR_OVERWRITE);
  }
  if (ft_strncmp(">>", token, ft_strlen(token)) == 0)
  {
    g_data.cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
    return (OUTPUT_REDIR_APPEND);
  }
  return (DEFAULT_MODE);
}

void	parse_single_cmd(int cmd_idx, int *token_idx)
{
	char	*token;
	int		mode;
	int		args_index;

	args_index = 0;
	mode = DEFAULT_MODE;
	while (*token_idx < g_data.cur.vec_tokens.len && is_delim_token(*token_idx) == 0)
	{
		token = get_token(*token_idx);
		mode = check_mode(token, cmd_idx);
		if (mode != DEFAULT_MODE) // if the token changes mode, we need the next token before going forward
		{
			free(token);
			*token_idx = *token_idx + 1;
			if (*token_idx < g_data.cur.vec_tokens.len) {
				token = get_token(*token_idx);
			}
		}
		if (g_data.cur.cmd_list[cmd_idx]->cmd == NULL && mode == DEFAULT_MODE) // If cmd has not been defined for this cmd struct
		{
			ft_printf("test 1\n");
      g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(token);
			g_data.cur.cmd_list[cmd_idx]->args = (char**)malloc(100*sizeof(char *));
			g_data.cur.cmd_list[cmd_idx]->args[args_index++] = ft_strdup(token);
			g_data.cur.cmd_list[cmd_idx]->path = get_command_path(token);
		}
		else if (mode == DEFAULT_MODE) // fill args
		{
		g_data.cur.cmd_list[cmd_idx]->args[args_index++] = ft_strdup(token);
		}
		else if (mode == INPUT_REDIR)
		{
			// TODO: validate that the token is valid (e.g. < > | are not valid)
			printf("cmd_idx = %d and g_data.cur.input == NULL : %d\n", cmd_idx, g_data.cur.input == NULL);
			if (cmd_idx == 0)
				g_data.cur.input = ft_strdup(token);
			else
				g_data.cur.cmd_list[cmd_idx]->input = ft_strdup(token);
			mode = DEFAULT_MODE;
		}
		else if (mode == OUTPUT_REDIR_APPEND || mode == OUTPUT_REDIR_OVERWRITE)
		{
			if (cmd_idx == g_data.cur.cmd_count - 1)
			{
				g_data.cur.output = ft_strdup(token);
				if (mode == OUTPUT_REDIR_APPEND)
					g_data.cur.output_mode = APPEND_MODE;
				else if (mode == OUTPUT_REDIR_OVERWRITE)
					g_data.cur.output_mode = OVERWRITE_MODE;
			}
			else
				g_data.cur.cmd_list[cmd_idx]->output = ft_strdup(token);
			mode = DEFAULT_MODE;
		}
		*token_idx = *token_idx + 1;
		free(token);
	}
}
