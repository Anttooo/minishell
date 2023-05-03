/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/11 17:17:29 by joonasmykka      ###   ########.fr       */
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
	}
	else
	{
		perror("problem with env");
		// Do clean exit here
	}
}