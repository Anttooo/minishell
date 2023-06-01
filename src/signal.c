/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 13:32:54 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_manager.h"
#include "../include/minishell.h"

extern t_data	g_data;

void	handle_ctrl_c(int sig)
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
			ioctl(1, TIOCSTI, nlc);
			rl_on_new_line();
		}
		else
			kill(g_data.sig.exec_pid, SIGINT);
	}
}

void	signal_manager(void)
{
	struct sigaction	act;

	act.sa_handler = handle_ctrl_c;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
}
