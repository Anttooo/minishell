/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/08 11:32:20 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

static void	execute_loop(char *input)
{
	if (input && *input)
		add_history(input);
	handle_input(input);
	if (g_data.cur.err_flag == 0)
		tokenize_input();
	// debug_print_tokens();
	if (g_data.cur.err_flag == 0)
		parse_commands();
	// debug_print_commands();
	if (g_data.cur.err_flag == 0)
		execute();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 && argv[1] != NULL)
		return (1);
	signal_manager();
	termios_settings();
	if (init_struct(envp) == 1)
		perror("init_struct");
	while (42)
	{
		input = readline(g_data.env.prompt);
		if (ft_strlen(input) != 0)
		{
			execute_loop(input);
			clean_cur_struct();
		}
		else if (input == NULL && g_data.sig.exec_pid == NO_CHILDS)
		{
			ft_exit();
		}
	}
	clean_exit_shell();
	return (g_data.env.exit_status);
}
