/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:57 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 17:110:22 by oanttoor         ###   ########.fr       */
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
	{
		execute_builtin();
		exit(0);
	}
	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	clean_exit_shell();
}

void	handle_input_redirection_for_first_cmd(t_pipes *p)
{
	if (p->idx == 0)
	{
		if (g_data.cur.input == NULL)
			p->fdin = STDIN;
		else
			redir_input(p);
		if (p->fdin != STDIN)
		{
			dup2(p->fdin, STDIN);
			close(p->fdin);
		}
	}
}

void	handle_output_redirection_for_last_cmd(t_pipes *p)
{
	ft_putstr_fd("are we setting the output redirection?\n", 2);
	if (p->idx == g_data.cur.cmd_count - 1)
	{
		ft_putstr_fd("setting the output redirection for last command\n", 2);
		ft_putstr_fd(g_data.cur.output, 2);
		ft_putstr_fd("  \n", 2);
		if (g_data.cur.output == NULL)
			p->fdout = STDOUT;
		else
			redir_out(p);
		if (p->fdout != STDOUT)
		{
			dup2(p->fdout, STDOUT);
			close(p->fdout);
		}
		ft_putnbr_fd(p->fdout, 2);
		ft_putstr_fd("  \n", 2);
	}
}

void	handle_pipes(t_pipes *p)
{
	close(p->pipes[p->idx][READ_END]);
	if (p->pipes[p->idx][WRITE_END] != STDOUT)
	{
		dup2(p->pipes[p->idx][WRITE_END], STDOUT);
		close(p->pipes[p->idx][WRITE_END]);
	}
}

void	handle_child(t_pipes *p)
{
	// Handle input redir
	handle_input_redirection_for_first_cmd(p);
	if (p->idx < g_data.cur.cmd_count - 1) // if not last command, handle pipes
	{
		handle_pipes(p);
	}
	handle_output_redirection_for_last_cmd(p);
	execute_cmd(p, p->idx);
}


void	handle_parent(t_pipes *p)
{
	if (p->fdin != STDIN)
	{
		close(p->fdin);
	}
	if (p->idx < g_data.cur.cmd_count - 1)
	{
		close(p->pipes[p->idx][WRITE_END]);
		p->fdin = p->pipes[p->idx][READ_END];
	}
}

void	command_loop(t_pipes *p)
{
	// Create pipes for every cmd but the last
	if (p->idx < g_data.cur.cmd_count - 1)
		pipe(p->pipes[p->idx]);
	g_data.sig.child_pid = fork();
	if (g_data.sig.child_pid == 0) // child process
	{
		handle_child(p);
	}
	else // Parent process
	{
		handle_parent(p);
	}
	g_data.cur.cmd_index++;
}

void	execute(void)
{
	t_pipes p;
	int		status;

	p.idx = 0;
	if (g_data.cur.cmd_count == 1 && is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin();
	else
	{
		p.fdin = STDIN;
		while (p.idx < g_data.cur.cmd_count) // while there are still commands to execute
		{
			command_loop(&p);
			p.idx++;
		}
		while (waitpid(-1, &g_data.env.exit_status, 0) > 0) // this waits for the commands to all finish
			;
		if (WIFEXITED(g_data.env.exit_status))
			g_data.env.exit_status = WEXITSTATUS(g_data.env.exit_status);
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
