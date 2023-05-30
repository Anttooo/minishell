/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 17:19:53 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

void	ft_export(void)
{
	return ;
}

// char	**ft_export(void)
// {
	// char	**append;
	// int		cmd_idx;
	// int		idx;

	// idx = -1;
	// cmd_idx = g_data.cur.cmd_index;
	// while (g_data.env.vars[++idx] != NULL)
	// 	;
	// append = (char **)malloc(sizeof(char *) * idx + 1);
	// if (!append)
	// {
	// 	// free garbage here
	// 	return (NULL);
	// }
	// idx = -1;
	// while (g_data.env.vars[++idx] != NULL)
	// 	append[idx] = ft_strdup(g_data.env.vars[idx]);
	// // Will need to check wherter args[1] is proper format, depends on
	// // the way we will tokenize input
	// append[idx] = ft_strdup(g_data.cur.cmd_list[cmd_idx]->args[1]);
	// append[++idx] = NULL;
	// free_arr(g_data.env.vars);
	// return (append);
// }
