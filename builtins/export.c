/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/05 11:05:17 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

extern t_data g_data;


// str should propably take the input data from global struct
// char	**ft_export(char *str)
// {
// 	char	**append;
// 	int		idx;
	
// 	printf("Using builtin function. \n");
// 	idx = -1;
// 	while (g_data.env.vars[++idx] != NULL)
// 		;
// 	idx++;
// 	append = (char **)malloc(sizeof(char *) * idx);
// 	if (!append)
// 		return (NULL);
// 	idx = -1;
// 	while (g_data.env.vars[++idx] != NULL)
// 		append[idx] = ft_strdup(g_data.env.vars[idx]);
// 	append[idx] = ft_strdup(str);
// 	append[++idx] = NULL;
// 	free_arr(g_data.env.vars);
// 	free(str);
// 	return (append);
// }