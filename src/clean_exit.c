/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:47:02 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 20:49:33 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

void	free_arr(char **arr)
{
	int	idx;

	idx = -1;
	while (arr[++idx] != NULL)
		free(arr[idx]);
	free(arr);
}

void	clean_exit_shell(void)
{
	if (g_data.dir.current)
	{
		free (g_data.dir.current);
		g_data.dir.current = NULL;
	}
	if (g_data.env.user)
	{
		free (g_data.env.user);
		g_data.env.user = NULL;
	}
	if (g_data.env.prompt)
	{
		free(g_data.env.prompt);
		g_data.env.prompt = NULL;
	}
}
