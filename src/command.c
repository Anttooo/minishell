/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/03/29 10:53:566 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/debug.h"

char	**get_paths(void)
{
	char	*env_vars;
	char	**paths;

	env_vars = getenv("PATH");
	if (!env_vars)
		return (NULL);
	paths = ft_split(env_vars, ':');
	// debug_print_list(paths, __func__);
	return (paths);
}

char *get_command_path(char *token)
{
	char	**paths;
	int		i;
	char	*cmd_path;
	char	*path_with_slash;

	i = 0;
	paths = get_paths(); // TODO: replace with paths saved in struct
	while (paths[i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path_with_slash, token);
		if(access(cmd_path, X_OK) == 0) {
			// printf("Command is an environment command, can be executed\n");
			return (cmd_path);
		}
		free(path_with_slash);
		free(cmd_path);
		i++;	
	}
	printf("command not found\n");
	return(NULL);
}

int	parse_input(char *input)
{
	char	**tokens;
	char	*command_path;
	// Separate the command from the argument to the command using split
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (-1);
	// print out tokens to see if they are separated correctly using a loop
	// Find the command path
	command_path = get_command_path(tokens[0]);
	execute_command(command_path, NULL, tokens);
	if (!command_path)
		return (-1);
	return (1);
}