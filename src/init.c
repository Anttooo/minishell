/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/23 17:14:01 by joonasmykka      ###   ########.fr       */
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
	vars = malloc(sizeof(char *) * idx);
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

void	set_builtins(void)
{
	g_data.dir.builtins[0] = "xxecho";
	g_data.dir.builtins[1] = "cd";
	g_data.dir.builtins[2] = "xxpwd";
	g_data.dir.builtins[3] = "xxexport";
	g_data.dir.builtins[4] = "xxunset";
	g_data.dir.builtins[5] = "xxenv";
	g_data.dir.builtins[6] = "xxexit";
}

// TODO Remember to add checks if opendir etc.. fails or not
void	init_directories(void)
{
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
	g_data.dir.ptr_current = opendir(g_data.dir.start);
	chdir(g_data.dir.ptr_current);
	g_data.dir.home = getenv("HOME");
	// g_data.dir.builtins = ft_strjoin(g_data.dir.start, "/builtins/executables/"); // TODO: fix this
	// TODO: Add error handling in case HOME directory can't for some reason be found from env.
	g_data.dir.current = ft_strdup(g_data.dir.start);
}

int	init_struct(char **envp)
{
	// init all args to null to start with
	set_builtins();
	g_data.sig.shell_pid = getpid();
	g_data.dir.start = (char *)malloc(1024);
	g_data.env.paths = get_paths();
	g_data.env.vars = get_env_vars(envp);
	g_data.env.user = find_env_var("USER");
	g_data.env.prompt = ft_strjoin(g_data.env.user, " --> ");
	init_directories();
  return (0);
}
