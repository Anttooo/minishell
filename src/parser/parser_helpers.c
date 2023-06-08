/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:11 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/08 11:21:49 by joonasmykka      ###   ########.fr       */
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

/*
	Counts cmds in input by counting unquoted pipes
*/
int	get_cmd_count(void)
{
	int		i;
	int		count;
	char	skip_char;

	i = 0;
	count = 1;
	while (g_data.cur.raw[i] != '\0')
	{
		if (g_data.cur.raw[i] == '|')
		{
			count++;
		}
		if (g_data.cur.raw[i] == '\"' || g_data.cur.raw[i] == '\'')
		{
			skip_char = g_data.cur.raw[i];
			i++;
			while (g_data.cur.raw[i] != skip_char && g_data.cur.raw[i] != '\0')
				i++;
		}
		i++;
	}
	g_data.cur.cmd_count = count;
	return (0);
}

int	allocate_cmd_list(void)
{
	unsigned long	size;
	int				i;

	i = 0;
	size = sizeof(t_cmd *);
	g_data.cur.cmd_list = (t_cmd **)malloc(g_data.cur.cmd_count * size);
	if (!g_data.cur.cmd_list)
	{
		perror("Error allocating command lists, will exit");
		clean_exit_shell();
		exit(errno);
	}
	while (i < g_data.cur.cmd_count)
	{
		if (parser_allocate(i) != 0)
			exit(errno);
		i++;
	}
	return (0);
}

// Checks the token type and if it's within_quotes, does not even compare it
int	is_delim(int i)
{
	t_token	*t;

	t = get_token(i);
	if (t->type == DEFAULT)
		if (ft_strncmp("|", t->token, ft_strlen(t->token)) == 0)
			return (1);
	return (0);
}

/* Handles checking if mode should be changed during parsing */
int	check_mode(char *token, int type, int cmd_idx)
{
	if (type == DEFAULT)
	{
		if (ft_strncmp("<", token, ft_strlen(token)) == 0)
		{
			return (INPUT_REDIR);
		}
		if (ft_strncmp(">", token, ft_strlen(token)) == 0)
		{
			g_data.cur.cmd_list[cmd_idx]->output_mode = OVERWRITE_MODE;
			return (OUTPUT_REDIR_OVERWRITE);
		}
		if (ft_strncmp(">>", token, ft_strlen(token)) == 0)
		{
			g_data.cur.cmd_list[cmd_idx]->output_mode = APPEND_MODE;
			return (OUTPUT_REDIR_APPEND);
		}
	}
	return (DEFAULT_MODE);
}
