/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 20:53:40 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

void	execute_cmd(t_pipes *p, int idx)
{
	char	*path;

	// printf("trying to execute %d \n", idx);
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
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
		// printf("NUMBER OF COMMANDS %d \n", g_data.cur.cmd_count);
		g_data.sig.exec_pid = fork();
		if (g_data.sig.exec_pid == 0)
		{
			init(&p);
			while (p.idx < g_data.cur.cmd_count - 1)
			{
				pipe(p.pipes[g_data.cur.cmd_index]);
				g_data.sig.child_pid = fork();
				if (g_data.sig.child_pid == 0)
				{
					// printf("CMD ID %d STARTED \n", p.idx);
					close(p.pipes[g_data.cur.cmd_index][READ_END]);
					dup2(p.pipes[g_data.cur.cmd_index][WRITE_END], STDOUT);
					execute_cmd(&p, g_data.cur.cmd_index);
				}
				else
				{
					close(p.pipes[g_data.cur.cmd_index][WRITE_END]);
					dup2(p.pipes[g_data.cur.cmd_index][READ_END], STDIN);
					// printf("going for next command \n");
				}
				g_data.cur.cmd_index++;
				p.idx++;
			}
			p.idx = -1;
			while (++p.idx < g_data.cur.cmd_count - 1)
			{
				wait(NULL);
			}
			// printf("ALL CHILDS HAVE RETURNED \n");
			pipe(p.pipes[g_data.cur.cmd_index]);	
			// printf("going for last command... id: %d\n", g_data.cur.cmd_index);
			execute_cmd(&p, g_data.cur.cmd_index);
		}
		else
		{
			// printf("waiting for main shit to return \n");
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
		ft_export();
	if (idx == 4)
		ft_unset();
	if (idx == 5)
		ft_env();
	if (idx == 6)
		ft_exit();
	free(cmd);
}