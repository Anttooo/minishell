/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/02 07:30:38 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(int argc, char **argv)
{
	printf("Using builtin function. \n");
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		return (1);
	}
	return (-1);
}