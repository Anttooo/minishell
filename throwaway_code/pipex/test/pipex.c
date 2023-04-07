/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:36:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/07 16:43:17 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>

typedef struct s_pipex_data 
{
	int			fdin;
	int			fdout;
	int			pipe[2];
	int			idx;
	pid_t		pid;
}				t_pipes;

typedef struct	s_data
{
	int		cmd_count;
	char	*input_file;
	char	*output_file;
}				t_data;

char	*env[] = {NULL};

char *arg_list[3][3] = {
        {"ls", NULL, NULL},
        {"sort", "-r", NULL},
        {"grep", "a", NULL}
    };

t_data	g_data;
char	**path_list;
char	**env_vars;

#define WRITE_END 1
#define READ_END 0

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char	**get_env_vars(char **envp)
{
	char	**vars;
	int		idx;

	idx = -1;
	while (envp[++idx] != NULL)
		;
	vars = malloc(sizeof(char *) * idx);
	if (!vars)
		return (NULL);
	idx = -1;
	while (envp[++idx] != NULL)
		vars[idx] = strdup(envp[idx]);
	vars[idx] = NULL;
	return (vars);
}

void	choose_input(t_pipes *p)
{
	if (g_data.input_file == NULL)
	{
		p->fdin = STDOUT;
	}
	else
	{
		p->fdin = open(g_data.input_file, O_RDONLY);
		if (p->fdin < 0)
		{
			perror("input file");
			// Do clean exit here
			exit(1);
		}
	}
}

void	choose_output(t_pipes *p)
{
	if (g_data.output_file == NULL)
	{
		p->fdout = STDOUT;
	}
	else
	{
		p->fdout = open(g_data.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fdout < 0)
		{
			perror("output file");
			// Do clean exit here
			exit(1);
		}
	}
}

// Choosing input and output to be file or stdin / stdout
// also redirecting those depending on chooses.
void	init(t_pipes *p)
{
	p->idx = -1;
	choose_input(p);
	choose_output(p);
	dup2(p->fdin, STDIN);
	dup2(p->fdout, STDOUT);
}

// only executes command and prints error if it fails
void	execute_cmd(t_pipes *p)
{
	printf("path: %s, args: %s %s", path_list[p->idx],  arg_list[p->idx][0],  arg_list[p->idx][1]);
	execve(path_list[p->idx], arg_list[p->idx], env_vars);
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
	}
}

void	pipex(void)
{
	t_pipes	p;

	// Init function
	init(&p);
	// Main loop will go trough all but one command
	while (++p.idx < g_data.cmd_count - 1)
		pipes_and_forks(&p);
	// last command gets executed witout redirections
	execute_cmd(&p);
}

int	main(int argc, char **argv, char **env)
{
	env_vars = get_env_vars(env);

	g_data.output_file = NULL;
	g_data.input_file = NULL;
	g_data.cmd_count = 3;

	// Allocate memory for path_list
    path_list = malloc(3 * sizeof(char*));
    path_list[0] = malloc(strlen("/bin/ls") + 1);
    strcpy(path_list[0], "/bin/ls");
    path_list[1] = malloc(strlen("/usr/bin/sort") + 1);
    strcpy(path_list[1], "/usr/bin/sort");
    path_list[2] = malloc(strlen("/usr/bin/grep") + 1);
    strcpy(path_list[2], "/usr/bin/grep");

	
	
	pipex();
	return (0);
}