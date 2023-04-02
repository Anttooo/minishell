/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/02 07:30:31 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export(int argc, char **argv, char **envp)
{
	printf("Using builtin function. \n");
	
	int i;

	i = 0;
	while (envp[i]) 
	{
		printf("%s\n", envp[i]);
		i++;
	}
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		return (1);
	}
	return (-1);
}