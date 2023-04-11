/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/11 10:57:54 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

extern t_data g_data;

void	ft_echo(void)
{
	int	idx;
	int	cmd_idx;

	idx = 0;
	cmd_idx = g_data.cur.cmd_index;
	while(g_data.cur.cmd_list[cmd_idx]->args[++idx] != NULL)
	{
		printf("%s", g_data.cur.cmd_list[cmd_idx]->args[idx]);
	}
	printf("\n");
	// Builtins probably need to exit since they will be called
	// in child process that needs to die before pipex parent
	// can move on
	exit(0);
}