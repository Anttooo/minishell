/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/12 15:24:56 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

// extern t_data g_data;

// char	**ft_export(void)
// {
// 	char	**append;
// 	int		idx;
	
// 	printf("Using builtin function. \n");
// 	idx = -1;
// 	while (g_data.env.vars[++idx] != NULL)
// 		;
// 	append = (char **)malloc(sizeof(char *) * idx + 1);
// 	if (!append)
// 		return (NULL);
// 	idx = -1;
// 	while (g_data.env.vars[++idx] != NULL)
// 		append[idx] = ft_strdup(g_data.env.vars[idx]);
// 	// global struct probably needs also a indexing on
// 	// what cmd are we executing
// 	// append[idx] = ft_strdup(g_data.cur.cmd_list[]);
// 	append[++idx] = NULL;
// 	free_arr(g_data.env.vars);
// 	free(str);
// 	return (append);
// }