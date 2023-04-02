/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:47:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/02 07:49:06 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(char **env_vars)
{
	int	idx;

	idx = -1;
	if (env_vars)
	{
		while (env_vars[++idx] != NULL)
			printf("%s \n", env_vars[idx]);
	}
}