/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 15:39:11 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"
#include "../include/minishell.h"

extern t_data	g_data;

char	**get_env_vars(char **envp)
{
	char	**vars;
	int		idx;

	idx = 0;
	while (envp[idx] != NULL)
		idx++;
	vars = malloc(sizeof(char *) * (idx + 1));
	string_array_malloc_error_check(vars);
	idx = 0;
	while (envp[idx] != NULL)
	{
		vars[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	vars[idx] = NULL;
	return (vars);
}

void	termios_settings(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
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

void	init_directories(void)
{
	g_data.dir.current = (char *)malloc(1024);
	malloc_error_check(g_data.dir.current);
	getcwd(g_data.dir.current, 1024);
	g_data.dir.ptr_current = opendir(g_data.dir.current);
	chdir(g_data.dir.current);
	g_data.dir.home = getenv("HOME");
}

int	init_struct(char **envp)
{
	set_builtins();
	g_data.cur.cmd_list = NULL;
	g_data.cur.heredoc_mode = 0;
	g_data.sig.shell_pid = getpid();
	g_data.sig.exec_pid = -1;
	g_data.env.exit_status = 0;
	g_data.env.vars = get_env_vars(envp);
	g_data.env.paths = get_paths();
	g_data.env.user = find_env_var("USER");
	g_data.env.prompt = ft_strjoin(g_data.env.user, " --> ");
	g_data.cur.err_flag = 0;
	init_directories();
	return (0);
}
