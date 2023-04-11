/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/11 11:31:49 by joonasmykka      ###   ########.fr       */
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
	vars = (char *)malloc(sizeof(char *) * idx);
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

int	init_struct(char **envp)
{
	g_data.shell_pid = getpid();
	g_data.dir.start = (char *)malloc(1024);
	g_data.env.paths = get_paths();
	g_data.env.vars = get_env_vars(envp);
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
	g_data.dir.home = getenv("HOME");
	// g_data.dir.builtins = ft_strjoin(g_data.dir.start, "/builtins/executables/"); // TODO: fix this
	// TODO: Add error handling in case HOME directory can't for some reason be found from env.
	if (chdir(g_data.dir.home) == -1) 
	{
		perror("chdir error in init_struct");
		return (1);
	}
	g_data.dir.current = g_data.dir.home;
  return (0);
}

void	init_for_new_input(void)
{
	// Might need more stuff here in future
	// This is bare minimum to make it work
	g_data.cur.cmd_index = 0;
	g_data.cur.cmd_count = 0;
}