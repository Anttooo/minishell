/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/03/30 22:18:20 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

int main(void)
{
    char    *input;

	if (init_struct() == 1)
	{
		perror("init_struct");
	}
    while (42) 
	{
		input = readline("sHeL>> ");
		if (!input)
		{
				printf("\n");
		}
		else
		{
			handle_input(input);
			free(input);
		}
    }
		clean_exit();
    return (0);
}
