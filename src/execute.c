/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 12:20:41 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

void	execute_cmd(t_pipes *p, int idx)
{
	char	*path;

	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
	if (g_data.cur.cmd_list[idx]->builtin == 1)
	{
		// perror("GOING TO EXECUTE BUILTIN");
		execute_builtin();
		clean_exit_shell();
		exit(0);
	}
	// printf("trying to execute %d \n", idx);
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	// printf("trying AGAIN to execute %d \n", idx);
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	// printf("execute cannot be done %d \n", idx);
	// perror("Error executing");
	clean_exit_shell();
	exit(1);
}

void	execute(void)
{
	t_pipes p;

	if (g_data.cur.cmd_count == 1 && is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin();
	else
	{
		g_data.sig.exec_pid = fork();
		if (g_data.sig.exec_pid == 0)
		{
			init(&p);
			// int pipefd[2];
			p.fdin = STDIN;

			for (p.idx = 0; p.idx < g_data.cur.cmd_count; p.idx++)
			{
				// Prepare the pipe for the next command, if there is one
				if (p.idx < g_data.cur.cmd_count - 1)
				{
					pipe(p.pipes[p.idx]);
				}

				g_data.sig.child_pid = fork();
				if (g_data.sig.child_pid == 0)
				{
					if (p.fdin != STDIN)
					{
						dup2(p.fdin, STDIN);
						close(p.fdin);
					}
					if (p.idx < g_data.cur.cmd_count - 1)
					{
						close(p.pipes[p.idx][READ_END]); // We don't need this in the current child
						if (p.pipes[p.idx][WRITE_END] != STDOUT)
						{
							dup2(p.pipes[p.idx][WRITE_END], STDOUT);
							close(p.pipes[p.idx][WRITE_END]);
						}
					}

					execute_cmd(&p, p.idx);
				}
				else
				{
					// Parent doesn't need these
					if (p.fdin != STDIN)
					{
						close(p.fdin);
					}
					if (p.idx < g_data.cur.cmd_count - 1)
					{
						close(p.pipes[p.idx][WRITE_END]);
						p.fdin = p.pipes[p.idx][READ_END];
					}
				}
			}

			// Wait for all child processes
			while (waitpid(-1, NULL, 0) > 0);

			exit(0);
		}
		else
		{
			// Parent just waits for the main child to finish
			waitpid(g_data.sig.exec_pid, NULL, 0);
			g_data.sig.exec_pid = -1;
		}
	}
}


// Function to execute one single builtin command
void	execute_builtin(void)
{
	char	*cmd;
	int		idx;

	cmd = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->cmd);
	idx = what_builtin(cmd);
	if (idx == 0)
		ft_echo();
	if (idx == 1)
		ft_cd();
	if (idx == 2)
		ft_pwd();
	if (idx == 3)
		ft_export(g_data.cur.cmd_index);
	if (idx == 4)
		ft_unset(g_data.cur.cmd_index);
	if (idx == 5)
		ft_env();
	if (idx == 6)
		ft_exit();
	free(cmd);
}