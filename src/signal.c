/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 17:01:37 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_manager.h"
#include "../include/minishell.h"

extern t_data	g_data;

static void	handle_int(int sig)
{
	const char	nlc[2] = {10, 0};
	const char	eof[2] = {4, 0};

	if (sig == SIGINT)
	{
		if (g_data.cur.heredoc_mode == 1)
		{
			g_data.cur.heredoc_mode = 0;
			g_data.cur.err_flag = 1;
			ioctl(1, TIOCSTI, eof);
		}
		if (g_data.sig.exec_pid == NO_CHILDS)
		{
			g_data.cur.err_flag = 1;
			rl_on_new_line();
			ioctl(1, TIOCSTI, nlc);
		}
		else
		{
			kill(g_data.sig.exec_pid, SIGINT);
		}
	}
}

static void	handle_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}

static void	init_sigint(void)
{
	struct sigaction	act;

	act.sa_handler = handle_int;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
}

static void	init_sigquit(void)
{
	struct sigaction	act;

	act.sa_handler = handle_quit;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_manager(void)
{
	init_sigint();
	init_sigquit();
}
