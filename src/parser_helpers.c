/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:11 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/17 16:55:19 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"
#include "../include/minishell.h"

extern t_data	g_data;
	
int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(g_data.dir.builtins[i], cmd, 10) == 0)
		{
			// return (1); // Commented out while builtins are not implemented.
      return (0);
		}
		i++;
	}
	return (0);
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
		printf("Command is a builtin\n");
		return("builtin");
	}
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