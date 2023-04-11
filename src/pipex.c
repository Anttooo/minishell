/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:36:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/11 11:03:59 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

extern t_data g_data;

// Choosing input and output to be file or stdin / stdout
// also redirecting those depending on chooses.
void	init(t_pipes *p)
{
	p->idx = -1;
	if (g_data.cur.input_file == NULL)
		p->fdin = STDOUT;
	else
	{
		p->fdin = open(g_data.cur.input_file, O_RDONLY);
		if (p->fdin < 0)
		{
			perror("input file");
			// Do clean exit here
			exit(1);
		}
	}
	if (g_data.cur.output_file == NULL)
		p->fdout = STDOUT;
	else
	{
		p->fdout = open(g_data.cur.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	path = ft_strdup(g_data.cur.cmd_list[idx]->path);
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

void	pipex(void)
{
	pid_t	child;
	t_pipes	p;

	char	*args[] = {g_data.cur.cmd_list[0]->cmd, g_data.cur.cmd_list[0]->args};

	child = fork();
	if (child)
	{
		// Init function
		init(&p);
		// Main loop will go trough all but one command
		while (++p.idx < g_data.cur.cmd_count - 1 && g_data.cur.cmd_count > 1)
			pipes_and_forks(&p);
		// last command gets executed witout redirections
		execute_cmd(&p);
	}
	else
	{
		waitpid(child, NULL, 0);
		// Since child cannot add the last cmd_index++ since it wont return from execve
		// parent will do it. After this cmd_index sould be == cmd_count
		// If this is the case, shell can return to input mode for more inputs
		g_data.cur.cmd_index++;
	}
}