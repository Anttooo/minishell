/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builltin_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:11:12 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 15:30:49 by joonasmykka      ###   ########.fr       */
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

int	get_env_var_count(void)
{
	int	i;

	i = 0;
	while (g_data.env.vars[i] != NULL)
		i++;
	return (i);
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

int	is_env_var(char *arg)
{
	int		idx;
	char	*needle;

	idx = -1;
	needle = ft_strjoin(arg, "=");
	while (g_data.env.vars[++idx] != NULL)
	{
		if (ft_strncmp(g_data.env.vars[idx], needle, ft_strlen(needle)) == 0)
		{
			free(needle);
			return (1);
		}
	}
	free(needle);
	return (0);
}
