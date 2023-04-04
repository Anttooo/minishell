/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/04 08:35:47 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	**export(char	**env_vars, char *str)
{
	char	**append;
	int		idx;
	
	printf("Using builtin function. \n");
	idx = -1;
	while (env_vars[++idx] != NULL)
		;
	idx++;
	append = (char **)malloc(sizeof(char *) * idx);
	if (!append)
		return (NULL);
	idx = -1;
	while (env_vars[++idx] != NULL)
		append[idx] = ft_strdup(env_vars[idx]);
	append[idx] = ft_strdup(str);
	append[++idx] = NULL;
	free_arr(env_vars);
	free(str);
	return (append);
}