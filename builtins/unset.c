/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:55:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/02 08:17:22 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static int	ft_name_len(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx] != '=' || str[++idx] != '\0')
		;
	return (idx);
}

static int	find_var(char **env_vars, char *name)
{
	int	idx;
	int	len;

	idx = -1;
	while (env_vars[++idx] != NULL)
	{
		if (ft_strcmp(env_vars[idx], name, ft_name_len(env_vars[idx])) != 0)
		{

		}
	}
	return (idx);
}

char	**unset(char **env_vars, char *name)
{
	
}