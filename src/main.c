/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/26 14:30:42 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

// static void	exec_check(void);
void  clean_cur_struct(void);

int main(int argc, char **argv, char **envp)
{
  char    *input;

	if (init_struct(envp) == 1)
	{
		perror("init_struct");
	}
	while (42)
	{
		signal_manager();
		input = readline(g_data.env.prompt);
		if (!input)
		{
				printf("\n");
		}
		else
		{
			if (input && *input)
				add_history(input);
			handle_input(input);
			if (g_data.cur.err_flag == 0)
				tokenize_input();
			debug_print_tokens();
			if (g_data.cur.err_flag == 0)
				parse_commands();
			debug_print_commands();
			if (g_data.cur.err_flag == 0)
				execute();
			free(input);
			clean_cur_struct();
		}
	}
	clean_exit_shell();
    return (0);
}

void  clean_cur_struct(void)
{
	int i;
  i = 0;
	free(g_data.cur.raw);
	if (g_data.cur.input)
	{
		free(g_data.cur.input);
		g_data.cur.input = NULL;
	}
	if (g_data.cur.output)
	{
		free(g_data.cur.output);
		g_data.cur.output = NULL;
	}
	if (g_data.cur.output_mode)
	{
		g_data.cur.output_mode = NULL;
	}
	vec_free(&g_data.cur.token_buffer);
	vec_free(&g_data.cur.tokens);
	vec_free(&g_data.cur.types);
	while (i < g_data.cur.cmd_count)
	{
		if (g_data.cur.cmd_list[i]->cmd)
			free(g_data.cur.cmd_list[i]->cmd);
		if (g_data.cur.cmd_list[i]->input)
			free(g_data.cur.cmd_list[i]->input);
		if (g_data.cur.cmd_list[i]->output)
			free(g_data.cur.cmd_list[i]->output);
		g_data.cur.cmd_list[i]->output_mode = NULL;
		if (g_data.cur.cmd_list[i]->args)
			free_arr(g_data.cur.cmd_list[i]->args);
		free(g_data.cur.cmd_list[i]);
		i++;
	}
	free(g_data.cur.cmd_list);
	g_data.cur.cmd_count = 0;
	g_data.cur.cmd_index = 0;
	g_data.cur.err_flag = 0;
}
