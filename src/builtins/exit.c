/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 17:30:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static void	handle_with_argument(int idx)
{
	if (ft_isvalid_int(g_data.cur.cmd_list[idx]->args[1]))
	{
		g_data.env.exit_status = ft_atoi(g_data.cur.cmd_list[idx]->args[1]);
		clean_exit_shell();
		exit(g_data.env.exit_status);
	}
	else
	{
		ft_putstr_fd("Shell: Exit: Numeric argument required\n", 2);
		g_data.env.exit_status = 255;
		clean_exit_shell();
		exit(g_data.env.exit_status);
	}
}

static void	handle_too_many_arguments(int idx)
{
	if (ft_isvalid_int(g_data.cur.cmd_list[idx]->args[1]))
	{
		if (g_data.cur.cmd_count == 1)
		{
			ft_putstr_fd("Shell: Exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			clean_exit_shell();
			ft_putstr_fd("Shell: Exit: too many arguments\n", 2);
			exit(255);
		}
	}
	clean_exit_shell();
	ft_putstr_fd("Shell: Exit: Numeric argument required\n", 2);
	g_data.env.exit_status = 255;
	exit(g_data.env.exit_status);
}

void	ft_exit(void)
{
	int	idx;
	int	len;

	idx = g_data.cur.cmd_index;
	len = arr_len();
	printf("exit\n");
	if (len == 1)
	{
		clean_exit_shell();
		exit(g_data.env.exit_status);
	}
	else if (len == 2)
		handle_with_argument(idx);
	else
		handle_too_many_arguments(idx);
}
