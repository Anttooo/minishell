/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/03/29 09:21:32 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
    char *input;

    while (42) {
        input = readline("sHeL>> ");
        if (!input) 
            printf("\n");
		else
		{
			if (handle_input(input) < 0)
			{
				printf("Error\n");
			}
		}
        free(input);
    }
    return (0);
}
