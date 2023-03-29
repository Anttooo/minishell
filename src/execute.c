/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:47:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/29 12:15:09 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include "../include/debug.h"

int	execute_command(char *command, char **options, char **args)
{
	char	*env[] = {NULL};
	// debug_print_list(args, __func__);
	if (execve(command, args, env) < 0)
		return (-1);
	return (1);
}