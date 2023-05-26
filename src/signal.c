/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/26 14:58:45 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal_manager.h"
#include "../include/minishell.h"

extern t_data	g_data;

void	termios_magic(void)
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

void	handle_ctrl_c(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	signal_magic(void)
{
	struct sigaction act;

	act.sa_handler = handle_ctrl_c;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
}

void	signal_manager(void)
{
	termios_magic();
	signal_magic();
}
