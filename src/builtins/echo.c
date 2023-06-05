/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 14:13:31 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	scan_for_options(int *ptr_idx)
{
    char	*arg;
    int i = 1;

    while (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[i] != NULL)
    {
        arg = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[i]);
        if (ft_strncmp(arg, "-n", ft_strlen(arg)) != 0)
        {
            *ptr_idx = i;
            return (0);
        }
        i++;
    }

    *ptr_idx = i;
    return (1);
}

int	ft_echo(int cmd_index)
{
    int	idx;
	int	printed_idx;

	printed_idx = 0;
    if (scan_for_options(&idx) == 0)
    {
        while (g_data.cur.cmd_list[cmd_idx]->args[idx] != NULL)
        {
            if (printed_idx > 1)
                printf(" ");
            printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
            idx++;
			printed_idx++;
        }
        printf("\n");
    }
    else
    {
        while (g_data.cur.cmd_list[cmd_idx]->args[idx] != NULL)
        {
            if (idx > 1)
                printf(" ");
            printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
            idx++;
			printed_idx++;
        }
    }
	return (0);
}

