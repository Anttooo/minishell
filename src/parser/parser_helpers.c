/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:11 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 14:03:52 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;
	
int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
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
		g_data.cur.cmd_list[i]->cmd = NULL;
		g_data.cur.cmd_list[i]->input = NULL;
		g_data.cur.cmd_list[i]->output = NULL;
		g_data.cur.cmd_list[i]->output_mode = NULL;
		i++;
	}
	return (0);
}
