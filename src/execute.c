/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:47:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/29 12:15:09 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include "../include/debug.h"

int	execute_command(char *command, char **options, char **args)
{
	pid_t	pid;
	char	*env[] = {NULL};
	// debug_print_list(args, __func__);

	pid = fork();
	if (pid < 0)
	{
		printf("Forking failed\n");
		//TODO: gracefully go back here
		return (1);
	}
	else if (pid == 0)
	{
		// we are in the child process when pid == 0
		execve(command, args, env);
	}
	else
	{
		// main process continues here
		wait(NULL);
		return (0);
	}
}