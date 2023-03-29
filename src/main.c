/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/03/29 08:57:44 by joonasmykka      ###   ########.fr       */
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
			input_handle(input);
        free(input);
    }
    return (0);
}
