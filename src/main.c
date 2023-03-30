/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/03/29 10:47:38 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_data	g_data;

int main(void)
{
    char    *input;

		init_struct();
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
