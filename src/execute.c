/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:36:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/23 11:12:52 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data g_data;

void	execute(void)
{
	t_pipes	p;

	g_data.sig.exec_pid = fork();
	if (g_data.sig.exec_pid == 0)
	{
		// Init function
		init(&p);
		// Main loop will go trough all but one command
		while (++p.idx < g_data.cur.cmd_count - 1 && g_data.cur.cmd_count > 1)
			pipes_and_forks(&p);
		// last command gets executed witout redirections
		execute_cmd(&p);
		exit(1);
	}
	else
	{
		waitpid(g_data.sig.exec_pid, NULL, 0);
		// Since child cannot add the last cmd_index++ since it wont return from execve
		// parent will do it. After this cmd_index sould be == cmd_count
		// If this is the case, shell can return to input mode for more inputs
		g_data.cur.cmd_index++;
	}
}

// Choosing input and output to be file or stdin / stdout
// also redirecting those depending on chooses.
void	init(t_pipes *p)
{
	p->idx = -1;
	if (g_data.cur.input == NULL)
		p->fdin = STDOUT;
	else
	{
		p->fdin = open(g_data.cur.input, O_RDONLY);
		if (p->fdin < 0)
		{
			perror("input file");
			// Do clean exit here
			exit(1);
		}
	}
	if (g_data.cur.output == NULL)
		p->fdout = STDOUT;
	else
	{
		if (g_data.cur.output_mode == APPEND_MODE)
			p->fdout = open(g_data.cur.output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (g_data.cur.output_mode == OVERWRITE_MODE)
			p->fdout = open(g_data.cur.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
		{
			printf("invalid output mode\n");
			// do clean exit here
			exit(1);
		}
		
		if (p->fdout < 0)
		{
			perror("output file");
			// Do clean exit here
			exit(1);
		}
	}
	dup2(p->fdin, STDIN);
	dup2(p->fdout, STDOUT);
}

// only executes command and prints error if it fails
void	execute_cmd(t_pipes *p)
{
	char	*path;
	int		idx;

	idx = g_data.cur.cmd_index;
	path = g_data.cur.cmd_list[idx]->path;
	// TODO create check if its builin or not
	// if (cmd_path == "builtin")
		// do builtin
	// else execve
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	perror("error executin");
	// do clean exit here
	exit(1);
}

void	pipes_and_forks(t_pipes *p)
{
	pipe(p->pipe);
	p->pid = fork();
	// Child process
	// will close read end since it is not needed here
	// redirects OUTPUT to pipes write end so that parent
	// can read it from there, will exit after execute
	if (p->pid == 0)
	{
		close(p->pipe[READ_END]);
		dup2(p->pipe[WRITE_END], STDOUT);
		execute_cmd(p);
	}
	// parent process
	// will close write end since it will only read from childs input
	// this is done by redirecting STDIN to pipes read end
	// Will wait for child prodcess to be done
	else
	{
		close(p->pipe[WRITE_END]);
		dup2(p->pipe[READ_END], STDIN);
		waitpid(p->pid, NULL, 0);
		g_data.cur.cmd_index++;
	}
}
