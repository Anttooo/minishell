/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:24:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 15:25:46 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

int	what_builtin(char *cmd)
{
	int	idx;

	idx = -1;
	while (++idx < 7)
	{
		if (ft_strncmp(cmd, g_data.dir.builtins[idx],
				ft_strlen(g_data.dir.builtins[idx])) == 0)
			break ;
	}
	return (idx);
}

void	update_env_paths(void)
{
	free_arr(g_data.env.paths);
	g_data.env.paths = get_paths();
}

char	*get_command_path(char *token)
{
	char	*path_with_slash;
	char	*cmd_path;
	int		i;

	if (is_builtin(token) == 1)
	{
		cmd_path = (ft_strdup("builtin"));
		return (cmd_path);
	}
	i = 0;
	update_env_paths();
	while (g_data.env.paths != NULL && g_data.env.paths[i])
	{
		path_with_slash = ft_strjoin(g_data.env.paths[i], "/");
		cmd_path = ft_strjoin(path_with_slash, token);
		free(path_with_slash);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return ("not found");
}
