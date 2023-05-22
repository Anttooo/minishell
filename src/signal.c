/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:07:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/17 10:13:38 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

void	parent(void)
{

}

void	child(void)
{
	struct sigaction action;

	sigemptyset(&action.sa_mask);
}

void	signal_manager(void)
{
	// if (g_data.sig.child_pid = fork())
	// 	parent();
	// else
	// 	child();
}
