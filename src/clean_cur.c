/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:35:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 14:30:23 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

static void	reset_cmd_struct(int i)
{
	if (g_data.cur.cmd_list[i]->cmd)
		free(g_data.cur.cmd_list[i]->cmd);
	if (g_data.cur.cmd_list[i]->input)
		free(g_data.cur.cmd_list[i]->input);
	if (g_data.cur.cmd_list[i]->output)
		free(g_data.cur.cmd_list[i]->output);
	g_data.cur.cmd_list[i]->output_mode = 0;
	if (g_data.cur.cmd_list[i]->args)
		free_arr(g_data.cur.cmd_list[i]->args);
	free(g_data.cur.cmd_list[i]);
}

static void	handle_heredoc_flag(void)
{
	if (g_data.cur.heredoc_flag == 1)
	{
		if (unlink("heredoc_temp_file") == -1)
		{
			perror("Error deleting the heredoc temp file");
			clean_exit_shell();
		}
		else
		{
			printf("\n** Heredoc temp file deleted ** \n");
		}
		g_data.cur.heredoc_flag = 0;
	}
}

static void	reset_fds(void)
{
	if (g_data.cur.input)
	{
		free(g_data.cur.input);
		g_data.cur.input = NULL;
	}
	if (g_data.cur.output)
	{
		free(g_data.cur.output);
		g_data.cur.output = NULL;
	}
}

void	clean_cur_struct(void)
{
	int	i;

	i = -1;
	free(g_data.cur.raw);
	reset_fds();
	vec_free(&g_data.cur.token_buffer);
	vec_free(&g_data.cur.tokens);
	vec_free(&g_data.cur.types);
	while (++i < g_data.cur.cmd_count)
		reset_cmd_struct(i);
	if (g_data.cur.cmd_list)
	{
		free(g_data.cur.cmd_list);
		g_data.cur.cmd_list = NULL;
	}
	g_data.cur.cmd_count = 0;
	g_data.cur.cmd_index = 0;
	g_data.cur.err_flag = 0;
	handle_heredoc_flag();
}
