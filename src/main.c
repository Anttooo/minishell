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

t_data	data;

int main(void)
{
    char    *input;

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
    return (0);
}

void	init_struct(void)
{
	
}
