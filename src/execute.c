/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:47:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/05 10:17:44 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
// #include "../include/minishell.h"
#include "../include/debug.h"

extern t_data	g_data;

int execute(void)
{
	pid_t	pid;
	char	*env[] = {NULL};
	char	*args[] = {g_data.cur.cmd_list[0]->cmd, g_data.cur.cmd_list[0]->args};
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
		execve(g_data.cur.cmd_list[0]->path, args, env);
	}
	else
	{
		// main process continues here
		wait(NULL);
		return (0);
	}
}
