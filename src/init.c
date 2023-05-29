/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/29 18:42:18 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"
#include "../include/minishell.h"

extern t_data	g_data;

char	**get_env_vars(char **envp)
{
	char	**vars;
	int		idx;

	idx = -1;
	while (envp[++idx] != NULL)
		;
	vars = malloc(sizeof(char *) * idx + 1);
	if (!vars)
		return (NULL);
	idx = -1;
	while (envp[++idx] != NULL)
		vars[idx] = ft_strdup(envp[idx]);
	vars[idx] = NULL;
	return (vars);
}

char	**get_paths(void)
{
	char	*env_vars;
	char	**paths;

	env_vars = getenv("PATH");
	if (!env_vars)
		return (NULL);
	paths = ft_split(env_vars, ':');
	// debug_print_list(paths, __func__);
	return (paths);
}

void	termios_settings(void)
{
	struct termios term;
	
	// Used to get current terminal settings to term struct
	tcgetattr(STDIN_FILENO, &term);
	// Setting c_lflag with ECHOCTL. It is wheter to print or not to print
	// control characters "~" is bitwise NOT operator that basicly makes it
	// turn to false. Default is true.
	term.c_lflag &= ~ECHOCTL;
	// Used to apply modified settings.
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_builtins(void)
{
	g_data.dir.builtins[0] = "echo";
	g_data.dir.builtins[1] = "cd";
	g_data.dir.builtins[2] = "pwd";
	g_data.dir.builtins[3] = "export";
	g_data.dir.builtins[4] = "unset";
	g_data.dir.builtins[5] = "env";
	g_data.dir.builtins[6] = "exit";
}

// TODO Remember to add checks if opendir etc.. fails or not
void	init_directories(void)
{
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
	g_data.dir.ptr_current = opendir(g_data.dir.start);
	g_data.dir.current = ft_strdup(g_data.dir.start);
	chdir(g_data.dir.current);
	g_data.dir.home = getenv("HOME");
	// g_data.dir.builtins = ft_strjoin(g_data.dir.start, "/builtins/executables/"); // TODO: fix this
	// TODO: Add error handling in case HOME directory can't for some reason be found from env.
}

int	init_struct(char **envp)
{
	// init all args to null to start with
	set_builtins();
	// Change settings on terminal
	g_data.cur.mode_heredoc = 0;
	g_data.sig.shell_pid = getpid();
	g_data.sig.exec_pid = -1;
	g_data.dir.start = (char *)malloc(1024);
	g_data.env.paths = get_paths();
	g_data.env.vars = get_env_vars(envp);
	g_data.env.user = find_env_var("USER");
	g_data.env.prompt = ft_strjoin(g_data.env.user, " --> ");
	g_data.cur.err_flag = 0;
	init_directories();
  return (0);
}
