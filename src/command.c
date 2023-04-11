/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/05 13:02:16 by oanttoor         ###   ########.fr       */
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

int get_cmd_count(void)
{
  // start from the beginning of the command, go character by character looking for pipes
  int 	i;
  int 	count;
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
  g_data.cur.cmd_count = count;
  ft_printf("nr of commands: %d\n", g_data.cur.cmd_count);
  return (0);
}

// malloc space for each command in g_data.cur.cmd_list
int	allocate_cmd_list(void)
{
	int	i;

	i = 0;
	g_data.cur.cmd_list = (t_cmd**)malloc(sizeof(t_cmd*) * g_data.cur.cmd_count);
	// TODO: replace with code that allocated space for each cmd
	while (i < g_data.cur.cmd_count)
	{
		g_data.cur.cmd_list[i] = (t_cmd*)malloc(sizeof(t_cmd));
		i++;
	}
	ft_printf("cmd list + %d instance(s) of t_cmd allocated\n", g_data.cur.cmd_count);
}

int	parse_each_command(void)
{
	
}

int	parse_input(void)
{
  char	**tokens;

	tokens = ft_split(g_data.cur.raw, ' ');
	if (!tokens)
		return (-1);

	get_cmd_count();
	allocate_cmd_list();
  
	// go through each command and store the things related to them in the struct
    // store the command
	g_data.cur.cmd_list[0]->cmd = ft_strdup(tokens[0]);
	g_data.cur.cmd_list[0]->path = ft_strdup(get_command_path(tokens[0]));
		if (!g_data.cur.cmd_list[0]->path)
		return (-1);
	// if the command can't be found, command_path is null and nothing should be done.
	
	// TODO: the args should take in an array as that's what execve takes in
	// TODO: we probably don't need to separate the options here but rather in the builtins which use options
	g_data.cur.cmd_list[0]->args = ft_strdup(tokens[1]);
    // get path for command -> if fails, quit
    // check for options
    // check for arguments
	return (0);
}

/*
int	parse_input(void)
{
	get_cmd_count(); - done
	allocate_cmd_list(); - done
	check_in_and_out_fd();
	parse_each_command(); 
}

*/
