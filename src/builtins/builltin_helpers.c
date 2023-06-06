/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builltin_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:11:12 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 14:27:06 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

void	free_env_vars(void)
{
	int	i;

	i = 0;
	while (g_data.env.vars[i] != NULL)
	{
		free (g_data.env.vars[i]);
		g_data.env.vars[i] = NULL;
		i++;
	}
	free (g_data.env.vars);
}

int		get_env_var_count(void)
{
	int	i;

	i = 0;
	while (g_data.env.vars[i] != NULL)
		i++;
	return (i);
}

int	ft_isnum(int c)
{
	if (c >= 47 && c <= 57)
		return (1);
	return (0);
}

int	arr_len(void)
{
	int	idx;

	idx = 0;
	if (g_data.cur.cmd_list == NULL)
		return (1);
	while (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[idx] != NULL)
		idx++;
	return (idx);
}

int	ft_isvalid_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] == '-' && str[1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
