/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/11 11:35:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

int main(int argc, char **argv, char **envp)
{
  char    *input;

	if (init_struct(envp) == 1)
	{
		perror("init_struct");
	}
    while (42)
	{
		input = readline("sHeL>> ");
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
     		// parse_input(void) -> gets data from struct
			parse_input();
      		// execute(void) -> gets data from struct
			pipex();
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
				printf("Error with executing\n");
				exit(1);
			}
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
