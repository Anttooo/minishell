/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:24:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 15:40:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

extern t_data g_data;

int	what_builtin(char *cmd)
{
	int	idx;

	idx = -1;
	while (++idx < 7)
	{
		if (ft_strncmp(cmd, g_data.dir.builtins[idx], ft_strlen(g_data.dir.builtins[idx])) == 0)
			break ;
	}
	return (idx);
}

void	update_env_paths(void)
{
	free_arr(g_data.env.paths);
	g_data.env.paths = get_paths();
}

char *get_command_path(char *token)
{
	int		i;
	char	*cmd_path;
	char	*path_with_slash;

	// TODO: restructure this code to check from an array of possible builtins, this code is invalid
	if(is_builtin(token) == 1) // 1 = true
	{
		cmd_path = (ft_strdup("builtin"));
		return(cmd_path);
	}
	i = 0;
	if (ft_strncmp(token, "./", 2) == 0) // if token starts with ./
	{
		
	}
	else
	{
		update_env_paths();
		while (g_data.env.paths != NULL && g_data.env.paths[i]) // TODO: should check from env rather than paths, or update paths first
		{
			path_with_slash = ft_strjoin(g_data.env.paths[i], "/");
			cmd_path = ft_strjoin(path_with_slash, token);
			free(path_with_slash);
			if(access(cmd_path, X_OK) == 0)
			{
				// printf("Command is an environment command, can be executed\n");
				return (cmd_path);
			}
			free(cmd_path); // MEMORY_LEAK: this does not get freed if the command is found
			i++;	
		}
		printf("command not found\n");
	}
	return("not found");
}