/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/03 12:52:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <signal.h>

// extern t_data g_data;

void	ft_exit(void)
{
	clean_exit();
	kill(g_data.sig.shell_pid, SIGTERM);
}