/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/08 16:15:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

int	do_checks(char *cmd)
{
	struct stat	statbuf;

	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("Shell: .: File name argument requiered\n", 2);
		exit(2);
	}
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode) != 0)
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
		execute_builtin(p);
	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args,
		g_data.env.vars);
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	ft_putstr_fd("Shell: ", 2);
	if (ft_strchr(g_data.cur.cmd_list[idx]->cmd, '/'))
	{
		ft_putstr_fd(g_data.cur.cmd_list[idx]->cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
	{
		ft_putstr_fd(g_data.cur.cmd_list[idx]->cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	clean_exit_shell();
	exit(errno);
}

void	command_loop(t_pipes *p)
{
	if (p->idx < g_data.cur.cmd_count - 1)
		pipe(p->pipes[p->idx]);
	g_data.sig.exec_pid = fork();
	if (g_data.sig.exec_pid == 0)
	{
		handle_child(p);
	}
	else
	{
		handle_parent(p);
	}
	g_data.cur.cmd_index++;
	p->idx++;
}
void	execute(void)
{
	int		original_stdin;
	t_pipes	p;

	p.idx = 0;
	if (g_data.cur.cmd_count == 1 \
		&& is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin(&p);
	else
	{
		original_stdin = dup(STDIN_FILENO);
		p.fdin = STDIN_FILENO;
		while (p.idx < g_data.cur.cmd_count)
		{
			command_loop(&p);
		}
		while (waitpid(-1, &g_data.env.exit_status, 0) > 0)
			;
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		if (WIFEXITED(g_data.env.exit_status))
			g_data.env.exit_status = WEXITSTATUS(g_data.env.exit_status);
	}
}
