/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/04 10:06:13 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

extern t_data g_data;


// str should propably take the input data from global struct
char	**export(char *str)
{
	char	**append;
	int		idx;
	
	printf("Using builtin function. \n");
	idx = -1;
	while (g_data.env.vars[++idx] != NULL)
		;
	idx++;
	append = (char **)malloc(sizeof(char *) * idx);
	if (!append)
		return (NULL);
	idx = -1;
	while (g_data.env.vars[++idx] != NULL)
		append[idx] = ft_strdup(g_data.env.vars[idx]);
	append[idx] = ft_strdup(str);
	append[++idx] = NULL;
	free_arr(g_data.env.vars);
	free(str);
	return (append);
}