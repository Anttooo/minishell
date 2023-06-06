/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 13:33:04 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	ft_isnum(int c)
{
	if (c >= 47 && c <= 57)
		return (1);
	return (0);
}

static int	ft_isvalid_int(char *str)
{
	int i;
	
	i = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] == '-' && str[1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(void)
{
	int idx;
	int	len;

	idx = g_data.cur.cmd_index;
	len = arr_len();
	printf("exit\n");
	if (len > 2)
	{
		ft_putstr_fd("Shell: Exit: too many arguments\n", 2);
		return ;
	}
	if (len == 1)
	{
		clean_exit_shell();
		exit(g_data.env.exit_status);
	}
	else if (len == 2)
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
	else
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
}

