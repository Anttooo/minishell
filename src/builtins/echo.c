/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 20:42:14 by oanttoor         ###   ########.fr       */
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

void	ft_echo(void)
{
    int	idx;
    int	cmd_idx;
	int	printed_idx;

    cmd_idx = g_data.cur.cmd_index;
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
}

