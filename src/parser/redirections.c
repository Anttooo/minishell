

#include "../../include/command.h"
#include "../../include/minishell.h"
#include "../../include/debug.h"

extern t_data	g_data;

/*
	Redirections can only accept certain tokens as arguments 
	and an invalid is a syntax error.
*/
int	is_valid_arg_for_redirection(char *token)
{
	if (ft_strncmp("|", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp("<", token, ft_strlen(token)) == 0)
		return (0);
	if (ft_strncmp(">", token, ft_strlen(token)) == 0)
		return (0);
	return (1);
}

int	handle_input_redirection(int cmd_idx, char *token, int *mode)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		g_data.cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	if (cmd_idx == 0)
		g_data.cur.input = ft_strdup(token);
	else
		g_data.cur.cmd_list[cmd_idx]->input = ft_strdup(token);
	*mode = DEFAULT_MODE;
	return (0);
}

int	handle_output_redirection(int cmd_idx, char *token, int *mode)
{
	if (is_valid_arg_for_redirection(token) == 0)
	{
		g_data.cur.err_flag = 1;
		printf("syntax error near unexpected token `%s'\n", token);
		return (1);
	}
	if (cmd_idx == g_data.cur.cmd_count - 1)
	{
		g_data.cur.output = ft_strdup(token);
		if (*mode == OUTPUT_REDIR_APPEND)
			g_data.cur.output_mode = APPEND_MODE;
		else if (*mode == OUTPUT_REDIR_OVERWRITE)
			g_data.cur.output_mode = OVERWRITE_MODE;
	}
	else
		g_data.cur.cmd_list[cmd_idx]->output = ft_strdup(token);
	*mode = DEFAULT_MODE;
	return (0);
}