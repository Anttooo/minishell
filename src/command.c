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
#include "../include/minishell.h"
#include "../include/debug.h"

extern t_data	g_data;

char *get_command_path(char *token)
{
	int		i;
	char	*cmd_path;
	char	*path_with_slash;

	// check whether the function is found from the builtins path
	cmd_path = ft_strjoin(g_data.dir.builtins, token);
	if(access(cmd_path, F_OK) == 0)
	{
		printf("Command is a builtin\n");
		return(cmd_path);
	}
	else
	{
		perror:("Error");
	}
	free(cmd_path);
	i = 0;
	while (g_data.env.paths[i])
	{
		path_with_slash = ft_strjoin(g_data.env.paths[i], "/");
		cmd_path = ft_strjoin(path_with_slash, token);
		if(access(cmd_path, X_OK) == 0) 
		{
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

int count_commands(void)
{
  // start from the beginning of the command, go character by character looking for pipes
  int i;
  int count;
  char  skip_char;

  i = 0;
  count = 1;
  while(g_data.cur.raw[i] != '\0')
  {
    if(g_data.cur.raw[i] == '|')
    {
      count++;
    }
    // if there is a single or double quote, skip until the same character is seen again
    if(g_data.cur.raw[i] == '\"' || g_data.cur.raw[i] == '\'')
    {
      skip_char = g_data.cur.raw[i];
      i++;
      while(g_data.cur.raw[i] != skip_char && g_data.cur.raw[i] != '\0')
        i++;
    }
    i++;
  } 
}

int	parse_input(void)
{
  count_commands();
  // check the number of commands
  // malloc space for each command in g_data.cur.cmd_list
  // check if the input or output fd should be changed
  // go through each command and store the things related to them in the struct
    // store the command
    // get path for command -> if fails, quit
    // check for options
    // check for arguments
  char	**tokens;
	char	*command_path;
	// This can only handle a single command
	tokens = ft_split(g_data.cur.raw, ' ');
	if (!tokens)
		return (-1);
	// print out tokens to see if they are separated correctly using a loop
	// Find the command path
	command_path = get_command_path(tokens[0]);
	// if the command can't be found, command_path is null and nothing should be done.
	if (!command_path)
		return (-1);
	return (0);
}
