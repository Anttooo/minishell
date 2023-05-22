/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/17 17:26:17 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"
#include "../include/debug.h"

extern t_data	g_data;


// Parse input takes in a perfect list of tokens and creates perfect command structs that can be passed to execute
int	parse_commands(void)
{
	// this is not needed after tokinzer is compele, it will pass on token list.
	// ***** Delete starts here ******
	// char	**tokens;
	// tokens = ft_split(g_data.cur.raw, ' '); // TODO: replace this will tokenize.c tokenizing
	// if (!tokens || tokens == NULL) // TODO: move this somewhere where it makes more sense to notice that there are no tokens
	// 	return (-1);
	
	/*
		g_data.cur.vec_tokens
			vec_tokens[0].token = cat
			vec_tokens[1].token = file1
			vec_tokens[2].token = |
			vec_tokens[3].token = sort
	*/

	// ****** Delete ends here ********

	int cmd_idx;
	int token_idx;

	cmd_idx = 0;
	token_idx = 0;
	get_cmd_count();
	allocate_cmd_list();
	while (cmd_idx < g_data.cur.cmd_count) {
		printf("Going into round %d\n", cmd_idx);
		parse_single_cmd(cmd_idx, &token_idx);
    token_idx++;
		cmd_idx++;
	}

	// // ******* THIS PART IS REPLACED WITH PARSE EACH COMMAND ******
	// // go through each command and store the things related to them in the struct
  //   // store the command
	// // This is kinda what the parse_each_command should be doing but in a loop for each command
	// g_data.cur.cmd_list[0]->cmd = ft_strdup(tokens[0]);
	// g_data.cur.cmd_list[0]->path = ft_strdup(get_command_path(tokens[0]));
	// 	if (!g_data.cur.cmd_list[0]->path)
	// 	return (-1);
	// // TODO: if the command can't be found, command_path is null and error should be given
	
	// g_data.cur.cmd_list[0]->args = ft_split(g_data.cur.raw, ' ');

	// // ****** REPLACED PART ENDS *******
	return (0);
}

char* get_token(int token_idx)
{
	t_token	*t;
	char	*token;
	
	// printf("in get token, token idx: %d\n", token_idx);
	t = (t_token *)vec_get(&g_data.cur.vec_tokens, token_idx);
	token = t->token;
	return (token);	
}

int	is_delim_token(int i)
{
	char *token;

	token = get_token(i);
	// strcmp token against the chars
	if (ft_strncmp("|", token, ft_strlen(token)) == 0)
	{
		printf("Seeing a delim token here\n");
		return (1);
	}
		
	return (0);
}

// void	parse_single_cmd(int cmd_idx, int *token_idx) // takes in the index of the cmd were handling
// {
// 	char	*token;
// 	// while there are tokens and the token isn't a delim
// 	while (token_idx < g_data.cur.vec_tokens.len && is_delim_token(token_idx) == FALSE)
// 	{
// 		token = get_token(token_idx);
// 		if (g_data.cur.cmd_list[i]->cmd == NULL) // If cmd has not been defined for this cmd struct
// 		{
// 			g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(token);
// 			g_data.cur.cmd_list[i]->path = get_cmd_path();
// 		}
// 		else // if the cmd has been defined the next thing could be either args or redir or redir's args
// 		{
			
// 		}
// 		free(token);
// 	}
// }

int  check_mode(char* token, int cmd_idx)
{
  // strncmp against '<', '>', '>>'
  if (ft_strncmp("<", token, ft_strlen(token)) == 0)
  {
    return (INPUT_REDIR);
  }
  if (ft_strncmp(">", token, ft_strlen(token)) == 0)
  {
    g_data.cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
    return (OUTPUT_REDIR);
  }
  if (ft_strncmp(">>", token, ft_strlen(token)) == 0)
  {
    g_data.cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
    return (OUTPUT_REDIR);
  }
  return (DEFAULT_MODE);
}

void	parse_single_cmd(int cmd_idx, int *token_idx) // takes in the index of the cmd were handling
{
	char	*token;
	int		mode;
	int		args_index;

	args_index = 0;
	mode = DEFAULT_MODE;
	// while there are tokens and the token isn't a delim
	// printf("token_idx: %d, vec_tokens.len: %d\n", *token_idx, g_data.cur.vec_tokens.len);
	while (*token_idx < g_data.cur.vec_tokens.len && is_delim_token(*token_idx) == 0)
	{
    token = get_token(*token_idx);
		printf("cmd index: %d, token: %s\n", cmd_idx, token);
    mode = check_mode(token, cmd_idx);
    if (mode != DEFAULT_MODE) // if the token changes mode, we need the next token before going forward
		{
			free(token);
			*token_idx = *token_idx + 1;
			if (*token_idx < g_data.cur.vec_tokens.len) {
				token = get_token(*token_idx);
			}
		}
    ft_printf("string value: %s\n", g_data.cur.cmd_list[cmd_idx]->cmd);
    ft_printf("mode: %d\n", mode);
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
      ft_printf("test 2\n");
      g_data.cur.cmd_list[cmd_idx]->args[args_index++] = ft_strdup(token);
		}
		else if (mode == INPUT_REDIR)
		{
			ft_printf("test 3\n");
      // TODO: validate that the token is valid (e.g. < > | are not valid)
			g_data.cur.cmd_list[cmd_idx]->input = ft_strdup(token);
			mode = DEFAULT_MODE;
		}
		else if (mode == OUTPUT_REDIR)
		{
			ft_printf("test 4\n");
      g_data.cur.cmd_list[cmd_idx]->output = ft_strdup(token);
			mode = DEFAULT_MODE;
		}
    ft_printf("test 5\n");
		*token_idx = *token_idx + 1;
		free(token);
	}
}
