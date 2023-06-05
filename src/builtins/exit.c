/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 13:30:47 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

void	ft_exit(void)
{
	int idx;

	idx = g_data.cur.cmd_index;
	printf("exit\n");
	clean_exit_shell();

	if (arr_len() == 2)
	{
		g_data.env.exit_status = ft_atoi(g_data.cur.cmd_list[idx]->args[1]);
		exit(g_data.env.exit_status);
	}
	else
	{
		ft_putstr_fd("Shell: Exit: Too many arguments\n", 2);
		g_data.cur.err_flag = 1;
	}
}
