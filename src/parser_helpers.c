/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:11 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 10:24:16 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data	g_data;
	
int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	ft_printf("checking if it's a builtin\n");
	while (i < 7)
	{
		if (ft_strncmp(g_data.dir.builtins[i], cmd, 10) == 0)
			return (1);
		i++;
	}
	return (0);
}


// start from the beginning of the command, go character by character looking for pipes
// if there is a single or double quote, skips until the same character is seen again
int get_cmd_count(void)
{

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
		g_data.cur.cmd_list[i]->args = NULL;
		g_data.cur.cmd_list[i]->path = NULL;
		g_data.cur.cmd_list[i]->cmd = NULL;
		g_data.cur.cmd_list[i]->input = NULL;
		g_data.cur.cmd_list[i]->output = NULL;
		g_data.cur.cmd_list[i]->output_mode = NULL;
		i++;
	}
	ft_printf("cmd list + %d instance(s) of t_cmd allocated\n", g_data.cur.cmd_count);
	return (0);
}

char *get_command_path(char *token)
{
	int		i;
	char	*cmd_path;
	char	*path_with_slash;

	// TODO: restructure this code to check from an array of possible builtins, this code is invalid
	if(is_builtin(token) == 1) // 1 = true
	{
		g_data.cur.cmd_list[g_data.cur.cmd_index]->builtin = 1;
		printf("Command is a builtin\n");
		cmd_path = (ft_strdup("builtin"));
		return(cmd_path);
	}
	ft_printf("*** NOT A BUILTIN!!!! ***\n");
	g_data.cur.cmd_list[g_data.cur.cmd_index]->builtin = 0;
	i = 0;
	while (g_data.env.paths[i])
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
	return(NULL);
}