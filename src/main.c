/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/24 10:32:49 by oanttoor         ###   ########.fr       */
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
	// handles signals for example ctrl + C
	signal_manager();
	while (42)
	{
		input = readline(g_data.env.prompt);
		if (!input)
		{
				printf("\n");
		}
		else
		{
			// TODO: add a function to set defaults of g_data.cur
			// g_data.cur.input = null
			// g_data.cur.output = null
			// store the input in struct
      if (input && *input)
        add_history(input);
			handle_input(input);
			tokenize_input();
      // print output from tokenize
      debug_print_tokens();
			parse_commands();
      debug_print_commands();
			// Set redirections
			execute();
			// exec_check(); // TODO: come up with a better way to check if all commands were executed
			free(input);
			
			clean_cur_struct();
		}
    }
	clean_exit(); // This function cleans all the data when the shell is closed
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
	vec_free(&g_data.cur.vec_tokens);
	while (i < g_data.cur.cmd_count)
	{
		if (g_data.cur.cmd_list[i]->cmd)
			free(g_data.cur.cmd_list[i]->cmd);
		if (g_data.cur.cmd_list[i]->path)
			free(g_data.cur.cmd_list[i]->path);
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
}

// This function does not work as the cmd_index can not be incremented from the child process, so it's value is always 1

// static void	exec_check(void)
// {
// 	if (g_data.cur.cmd_index == g_data.cur.cmd_count)
// 	{
// 		// Executing all commands succeeded, reset variables that needs to be
// 		// resetted and keep going for more inputs
// 		reset_cur();
// 	}
// 	else
// 	{
// 		// something went wrong when executing... need to figure out how to handle
// 		// that here.
// 		printf("cmd_idx: %d and cmd count: %d \n", g_data.cur.cmd_index, g_data.cur.cmd_count);
// 		printf("Error with executing\n");
// 		exit(1);
// 	}
// }
