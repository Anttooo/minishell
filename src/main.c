/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/05 10:37:53 by oanttoor         ###   ########.fr       */
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
      		// store the input in struct + TODO: add in history
			handle_input(input);
     		// parse_input(void) -> gets data from struct
			parse_input();
      		// execute(void) -> gets data from struct
			execute();
			// the free below could be replaced by a cleaning function
			free(input);
			// TODO: add freeing to all things within g_data.cur
				// g_data.cur.cmd_list
				// g_data.cur.cmd_list[i]
				// g_data.cur.cmd_list[i].path, cmd, args, options
			free(g_data.cur.raw);
		}
    }
	clean_exit(); // This function cleans all the data when the shell is closed
    return (0);
}
