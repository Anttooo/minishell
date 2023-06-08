/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:54 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/08 11:22:08 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error_check(char *string)
{
	if (!string)
	{
		perror("");
		clean_exit_shell();
		exit(errno);
	}
}

void	string_array_malloc_error_check(char **string)
{
	if (!string)
	{
		perror("");
		clean_exit_shell();
		exit(errno);
	}
}
