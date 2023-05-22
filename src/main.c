/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/17 17:06:46 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

static void	exec_check(void);

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
			// store the input in struct + TODO: add in history
			handle_input(input);
			tokenize_input();
			parse_commands();
			// Set redirections
			execute();
			exec_check();
			// the free below could be replaced by a cleaning function
			free(input);
			// TODO: add freeing to all things within g_data.cur
				// g_data.cur.cmd_list
				// g_data.cur.cmd_list[i]
				// g_data.cur.cmd_list[i].path, cmd, args, options
				// g_data.cur.input & output
			free(g_data.cur.raw);
		}
    }
	clean_exit(); // This function cleans all the data when the shell is closed
    return (0);
}

static void	exec_check(void)
{
	if (g_data.cur.cmd_index == g_data.cur.cmd_count)
	{
		// Executing all commands succeeded, reset variables that needs to be
		// resetted and keep going for more inputs
		reset_cur();
	}
	else
	{
		// something went wrong when executing... need to figure out how to handle
		// that here.
		printf("cmd_idx: %d and cmd count: %d \n", g_data.cur.cmd_index, g_data.cur.cmd_count);
		printf("Error with executing\n");
		exit(1);
	}
}
