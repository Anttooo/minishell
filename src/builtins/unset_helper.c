/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:58:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 18:58:52 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

// add the functio nto extract until first '=' here
char	*extract_until_equal(char *arg)
{
	int		i;
	char	*result;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	malloc_error_check(result);
	ft_strlcpy(result, arg, i + 1);
	return (result);
}
