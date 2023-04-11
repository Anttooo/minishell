/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/11 10:40:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

extern t_data g_data;

void	ft_env(void)
{
	int	idx;

	idx = -1;
	if (g_data.env.vars)
	{
		while (g_data.env.vars[++idx] != NULL)
			printf("%s \n", g_data.env.vars[idx]);
		exit(0);
	}
	else
	{
		perror("problem with env");
		// Do clean exit here
		exit(1);
	}
}