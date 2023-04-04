/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/04 15:49:55 by joonasmykka      ###   ########.fr       */
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
      // store the input in struct + later in history
			handle_input(input);
      // parse_input(void) -> gets data from struct
      // execute(void) -> gets data from struct
			// the free below could be replaced by a cleaning function
      free(input);
      free(g_data.cur.raw);
		}
    }
		clean_exit(); // This function cleans all the data when the shell is closed
    return (0);
}

/* 
int main {
  - initialise
  while (42)
  {
    - wait for input (readline: )
    - take in input -> Puts input in struct current + history
    - parse input -> Formats input in struct command
    - execute command -> basically pipex
    - clean -> empties data
  }
}

*/
