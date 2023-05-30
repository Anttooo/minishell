#include "../../include/command.h"
#include "../../include/minishell.h"
#include "../../include/debug.h"

extern t_data	g_data;

void	handle_cmd(int cmd_idx, char *token, int *args_index)
{
	g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(token);
	g_data.cur.cmd_list[cmd_idx]->args = (char**)malloc(100 * sizeof(char *));
	g_data.cur.cmd_list[cmd_idx]->args[(*args_index)++] = ft_strdup(token);
}

void	handle_args(int cmd_idx, char *token, int *args_index)
{
	g_data.cur.cmd_list[cmd_idx]->args[*args_index] = ft_strdup(token);
	(*args_index)++;
}

void	handle_cmd_and_args(int cmd_idx, char *token, int *args_index)
{
	if (g_data.cur.cmd_list[cmd_idx]->cmd == NULL)
		handle_cmd(cmd_idx, token, args_index);
	else
		handle_args(cmd_idx, token, args_index);
}
