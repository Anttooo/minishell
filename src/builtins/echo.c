/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:04:33 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 15:27:01 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	is_option_n(char *arg)
{
	if (ft_strncmp(arg, "-n", ft_strlen(arg)) == 0)
	{
		return (1);
	}
	return (0);
}

static int	has_option_n(int *ptr_idx)
{
	int	i;
	int	has_option_n;

	i = 1;
	has_option_n = 0;
	while (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[i] != NULL)
	{
		if (is_option_n(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[i]))
		{
			(*ptr_idx)++;
			has_option_n = 1;
		}
		i++;
	}
	return (has_option_n);
}

static void	with_option(int cmd_idx, int idx, int printed_idx)
{
	while (g_data.cur.cmd_list[cmd_idx]->args[idx] != NULL)
	{
		if (printed_idx > 0)
			printf(" ");
		printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
		idx++;
		printed_idx++;
	}
	printf("\n");
}

static void	without_option(int cmd_idx, int idx)
{
	while (g_data.cur.cmd_list[cmd_idx]->args[idx] != NULL)
	{
		if (cmd_idx > 0)
			printf(" ");
		printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
		idx++;
		cmd_idx++;
	}
}

int	ft_echo(int cmd_idx)
{
	int	idx;
	int	printed_idx;

	printed_idx = 0;
	idx = 1;
	if (has_option_n(&idx) == 0)
	{
		with_option(cmd_idx, idx, printed_idx);
	}
	else
	{
		without_option(cmd_idx, idx);
	}
	return (0);
}
