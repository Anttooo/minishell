/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 16:06:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

int do_checks(char *cmd)
{
	struct stat statbuf;

	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("Shell: .: File name argument requiered\n", 2);
		exit(2);
	}
	if (stat(cmd, &statbuf) != 0)
	{
		perror("\n");
		clean_exit_shell();
		exit(errno);
	}
	if (statbuf.st_mode != 0)
	{
		ft_putstr_fd("Shell: /: is a directory\n", 2);
		exit(126);
	}
	return (0);
}

void	execute_cmd(t_pipes *p, int idx)
{
	char	*path;

	do_checks(g_data.cur.cmd_list[idx]->cmd);
	if (is_builtin(g_data.cur.cmd_list[idx]->cmd) == 1)
	{
		execute_builtin();
		exit(0);
	}
	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	clean_exit_shell();
	exit(errno);
}

void	execute(void)
{
	t_pipes p;
	int		status;

	if (g_data.cur.cmd_count == 1 && is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin();
	else
	{
		init(&p);
		p.fdin = STDIN;

		for (p.idx = 0; p.idx < g_data.cur.cmd_count; p.idx++)
		{
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
					close(p.pipes[p.idx][READ_END]);
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
			g_data.cur.cmd_index++;
		}
		while (waitpid(-1, &g_data.env.exit_status, 0) > 0)
			;
		if (WIFEXITED(g_data.env.exit_status))
		{
			g_data.env.exit_status = WEXITSTATUS(g_data.env.exit_status);
		}
	}
}


// Function to execute one single builtin command
int	execute_builtin(void)
{
	char	*cmd;
	int		idx;

	cmd = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->cmd);
	idx = what_builtin(cmd);
	if (idx == 0)
		return (ft_echo(g_data.cur.cmd_index));
	if (idx == 1)
		return (ft_cd());
	if (idx == 2)
		return (ft_pwd());
	if (idx == 3)
		return (ft_export(g_data.cur.cmd_index));
	if (idx == 4)
		return (ft_unset(g_data.cur.cmd_index));
	if (idx == 5)
		return (ft_env());
	if (idx == 6)
		ft_exit();
	free(cmd);
	return (0);
}