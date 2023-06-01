/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 18:50:03 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

int	is_valid_env_variable_value(char *arg)
{
	if (arg[0] == '\0')
		return (0);
	ft_printf("Env var value: %s\n", arg);
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
		ft_printf("There was no equal sing.\n");
		is_valid = 0;
	}
	if(is_valid == 1 && is_valid_env_variable_name(arg) != 1)
	{
		ft_printf("The name was not valid\n");
		is_valid = 0;
	}
	if(is_valid == 1 && is_valid_env_variable_value(equal_sign_ptr + 1) != 1)
	{
		ft_printf("The value was not valid\n");
		is_valid = 0;
	}
	return (is_valid);
}

int		get_env_var_count(void)
{
	int	i;

	i = 0;
	while (g_data.env.vars[i] != NULL)
		i++;
	return (i);
}

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

char	**add_arg_to_env_vars(char *arg)
{
	char	**new_env_vars;
	int		i;

	i = 0;
	printf("Number of env vars: %d, arg to be added: %s\n", get_env_var_count(), arg);
	// malloc string array one larger than the current env vars + null terminator 
	new_env_vars = (char **)malloc((get_env_var_count() + 2) * sizeof(char *));
	if (!new_env_vars)
	{
		// handle error
	}
	// copy the current env vars to a temp holder
	// add all the current env vars into the new array
	while (g_data.env.vars[i] != NULL)
	{
		new_env_vars[i] = ft_strdup(g_data.env.vars[i]);
		i++;
	}
	// add the new env variable
	new_env_vars[i] = ft_strdup(arg);
	// Null terminate the variable
	new_env_vars[i + 1] = NULL;
	// free all the variables in g_data.env.vars and the entire g_data.cur.vars after that.
	// free g_data.env.vars
	free_env_vars();
	return (new_env_vars);
}

void	handle_export_argument(char *arg)
{
	ft_printf("Current argument: %s\n", arg);
	if(is_valid_identifier(arg) == 1)
	{
		ft_printf("Valid identifier\n");
		g_data.env.vars = add_arg_to_env_vars(arg);
	}
	else
		ft_printf("export: `%s': not a valid identifier\n", arg);
}

void	ft_export(int cmd_idx)
{
	int	i;
	int	env_var_idx;

	i = 1;
	env_var_idx = 0;
	ft_printf("Command index: %d\n", cmd_idx);
	// input value: all arguments given to export
	// go through them one by one so if there's an error with one of them, it does not prevent from adding the ones before
	// Also if there are problems while adding multiple, the process does not stop at invalid identified
	if (g_data.cur.cmd_list[cmd_idx]->args[1] == NULL)
	{
		ft_printf("No arguments were given.\n");
		// without arguments, prints out env vars with declare-x before each
		while (g_data.env.vars[env_var_idx] != NULL)
		{
			ft_printf("declare -x %s\n", g_data.env.vars[env_var_idx]);
			env_var_idx++;
		}
	}
	while (g_data.cur.cmd_list[cmd_idx]->args[i] != NULL)
	{
		handle_export_argument(g_data.cur.cmd_list[cmd_idx]->args[i]);
		i++;
	}
}
