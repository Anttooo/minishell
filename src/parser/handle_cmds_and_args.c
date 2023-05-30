#include "../../include/command.h"
#include "../../include/minishell.h"
#include "../../include/debug.h"

extern t_data	g_data;

void	handle_cmd(int cmd_idx, t_token *t, int *args_index)
{
	g_data.cur.cmd_list[cmd_idx]->cmd = ft_strdup(t->token);
	g_data.cur.cmd_list[cmd_idx]->args = (char**)malloc(100 * sizeof(char *));
	g_data.cur.cmd_list[cmd_idx]->args[(*args_index)++] = ft_strdup(t->token);
}

void	handle_args(int cmd_idx, t_token *t, int *args_index)
{
	debug_print_string(t->token, __func__);
	printf("Args index: %d\n", *args_index);
	g_data.cur.cmd_list[cmd_idx]->args[*args_index] = ft_strdup(t->token);
	(*args_index)++;
}

void	handle_cmd_and_args(int cmd_idx, t_token *t, int *args_index)
{
	if (g_data.cur.cmd_list[cmd_idx]->cmd == NULL)
		handle_cmd(cmd_idx, t, args_index);
	else
		handle_args(cmd_idx, t, args_index);
}
