/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:36:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 15:24:50 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

// Since child cannot add the last cmd_index++ since it wont return from execve
// parent will do it. After this cmd_index sould be == cmd_count
// If this is the case, shell can return to input mode for more inputs
void	execute(void)
{
	t_pipes	p;

	if (g_data.cur.cmd_count == 1 && is_builtin(g_data.cur.cmd_list[0]->cmd) == 1)
		execute_builtin();
	else
	{
		g_data.sig.exec_pid = fork();
		if (g_data.sig.exec_pid == 0)
		{
			init(&p);
			while (++p.idx < g_data.cur.cmd_count - 1 && g_data.cur.cmd_count > 1)
			{
				pipes_and_forks(&p);
			}
			execute_cmd();
			exit(1);
		}
		else
		{
			waitpid(g_data.sig.exec_pid, NULL, 0);
			g_data.cur.cmd_index++;
		}
		g_data.sig.exec_pid = -1;
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
			// TODO: Do clean exit here
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
			// TODO: do clean exit here
			exit(1);
		}
		if (p->fdout < 0)
		{
			perror("output file");
			// TODO: Do clean exit here
			exit(1);
		}
	}
	dup2(p->fdin, STDIN);
	dup2(p->fdout, STDOUT);
}

char *get_command_path(char *token)
{
	int		i;
	char	*cmd_path;
	char	*path_with_slash;

	// TODO: restructure this code to check from an array of possible builtins, this code is invalid
	if(is_builtin(token) == 1) // 1 = true
	{
		g_data.cur.cmd_list[g_data.cur.cmd_index]->builtin = 1;
		cmd_path = (ft_strdup("builtin"));
		return(cmd_path);
	}
	g_data.cur.cmd_list[g_data.cur.cmd_index]->builtin = 0;
	i = 0;
	if (ft_strncmp(token, "./", 2) == 0) // if token starts with ./
	{
		
	}
	else
	{
		while (g_data.env.paths[i])
		{
			path_with_slash = ft_strjoin(g_data.env.paths[i], "/");
			cmd_path = ft_strjoin(path_with_slash, token);
			free(path_with_slash);
			if(access(cmd_path, X_OK) == 0)
			{
				// printf("Command is an environment command, can be executed\n");
				return (cmd_path);
			}
			free(cmd_path); // MEMORY_LEAK: this does not get freed if the command is found
			i++;	
		}
		printf("command not found\n");
	}
	return("not found");
}

/*
	First tries to execute using absolute path and if that fails, uses get command path
*/
void	execute_cmd(void)
{
	char	*path;
	int		idx;

	idx = g_data.cur.cmd_index;
	execve(g_data.cur.cmd_list[idx]->cmd, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	path = get_command_path(g_data.cur.cmd_list[idx]->cmd);
	execve(path, g_data.cur.cmd_list[idx]->args, g_data.env.vars);
	printf("Error: %s\n", strerror(errno));
	clean_exit_shell();
}

void	pipes_and_forks(t_pipes *p)
{
	pipe(p->pipe);
	p->pid = fork();
	if (p->pid == 0)
	{
		close(p->pipe[READ_END]);
		dup2(p->pipe[WRITE_END], STDOUT);
		execute_cmd();
	}
	else
	{
		close(p->pipe[WRITE_END]);
		dup2(p->pipe[READ_END], STDIN);
		waitpid(p->pid, NULL, 0);
		g_data.cur.cmd_index++;
	}
}

int	what_builtin(char *cmd)
{
	int	idx;

	idx = -1;
	while (++idx < 7)
	{
		if (ft_strncmp(cmd, g_data.dir.builtins[idx], ft_strlen(g_data.dir.builtins[idx])) == 0)
			break ;
	}
	return (idx);
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
		ft_unset();
	if (idx == 5)
		ft_env();
	if (idx == 6)
		ft_exit();
	free(cmd);
}
