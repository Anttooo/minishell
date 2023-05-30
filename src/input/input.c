/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:19:52 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 18:22:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/input.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;

// TODO: add error handling 
int	handle_input(char *input)
{
	if (strcmp(input, "quit") == 0)
	{
		free(input);
		exit(0);
	}
	else
	{
		while (is_multiline(input) != 0)
			handle_multiline(&input);
		g_data.cur.raw = ft_strdup(input);
	}
	return (0);
}
