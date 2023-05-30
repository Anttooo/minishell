/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 17:18:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	scan_for_options(int *ptr_idx)
{
	char	*arg;

	if (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[1] != NULL)
	{
		arg = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[1]);
		if (ft_strnstr(arg, "-n", ft_strlen(arg)) != NULL)
		{
			*ptr_idx += 1;
			return (1);
		}
	}
	return (0);
}

void	ft_echo(void)
{
	int	idx;
	int	cmd_idx;

	idx = 0;
	cmd_idx = g_data.cur.cmd_index;
	if (scan_for_options(&idx) == 0)
	{
		while (g_data.cur.cmd_list[cmd_idx]->args[++idx] != NULL)
			printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
		printf("\n");
	}
	else
	{
		while (g_data.cur.cmd_list[cmd_idx]->args[++idx] != NULL)
			printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
	}
}
