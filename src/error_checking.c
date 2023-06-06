/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:54 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 14:53:22 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void	malloc_error_check(char *string)
{
	if (!string)
	{
		perror("");
		clean_exit_shell();
		exit (errno);
	}
}