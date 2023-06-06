/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 18:00:20 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

int	is_valid_env_variable_value(char *arg)
{
	if (arg[0] == '\0')
		return (0);
	return (1);
}

int	is_valid_env_variable_name(char *arg)
{
	int	i;

	i = 0;
	if (is_valid_first_character(arg[i]) != 1)
		return (0);
	i++;
	while (arg[i] != '=')
	{
		if (is_valid_subsequent_character(arg[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(char *arg)
{
	char	*equal_sign_ptr;
	int		is_valid;

	is_valid = 1;
	equal_sign_ptr = ft_strchr(arg, '=');
	if (equal_sign_ptr == NULL)
	{
		is_valid = 0;
	}
	if (is_valid == 1 && is_valid_env_variable_name(arg) != 1)
	{
		is_valid = 0;
	}
	if (is_valid == 1 && is_valid_env_variable_value(equal_sign_ptr + 1) != 1)
	{
		is_valid = 0;
	}
	return (is_valid);
}

char	**add_arg_to_env_vars(char *arg)
{
	char	**new_env_vars;
	int		i;

	i = 0;
	new_env_vars = (char **)malloc((get_env_var_count() + 2) * sizeof(char *));
	string_array_malloc_error_check(new_env_vars);
	while (g_data.env.vars[i] != NULL)
	{
		new_env_vars[i] = ft_strdup(g_data.env.vars[i]);
		i++;
	}
	new_env_vars[i] = ft_strdup(arg);
	new_env_vars[i + 1] = NULL;
	free_env_vars();
	return (new_env_vars);
}

int	ft_export(int cmd_idx)
{
	int		env_var_idx;
	char	*arg;
	int		i;

	i = 1;
	env_var_idx = 0;
	arg = ft_strdup(g_data.cur.cmd_list[cmd_idx]->args[i]);
	if (g_data.cur.cmd_list[cmd_idx]->args[1] == NULL)
	{
		while (g_data.env.vars[env_var_idx] != NULL)
			env_var_idx++;
	}
	while (g_data.cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		if (is_valid_identifier(arg) == 1)
		{
			ft_unset(cmd_idx, EXPORT);
			g_data.env.vars = add_arg_to_env_vars(arg);
		}
		else
			ft_printf("export: `%s': not a valid identifier\n", arg);
		i++;
	}
	return (0);
}
