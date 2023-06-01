/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:55:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 20:34:09 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

int	is_var_to_be_removed(char *to_be_removed, char *current_env_var)
{
	char	*needle;

	needle = ft_strjoin(to_be_removed, "=");
	if (ft_strncmp(current_env_var, needle, ft_strlen(needle)) == 0)
		return (1);
	free(needle);
	return (0);
}

char	**remove_env_var(char *arg)
{
	char	**new_env_vars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env_vars = (char **)malloc(get_env_var_count() * sizeof(char *));
	if (!new_env_vars)
	{
		// handle error
	}
	while (g_data.env.vars[i] != NULL)
	{
		if (is_var_to_be_removed(arg, g_data.env.vars[i]) == 0)
		{
			new_env_vars[j] = ft_strdup(g_data.env.vars[i]);
			j++;
		}
		i++;
	}
	new_env_vars[i] = NULL;
	free_env_vars();
	return (new_env_vars);
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
			free (needle);
			return (1);
		}
	}
	free(needle);
	return (0);
}

void	handle_unset_env_var(char *arg)
{
	if (is_env_var(arg) == 1)
		g_data.env.vars = remove_env_var(arg);
}

void	ft_unset(int cmd_idx)
{
	int	i;

	i = 1;
	while (g_data.cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		handle_unset_env_var(g_data.cur.cmd_list[cmd_idx]->args[i]);
		i++;
	}
}
