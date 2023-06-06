/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:13:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 15:44:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/init.h"

extern t_data	g_data;

void	reset_cur(void)
{
	g_data.cur.cmd_index = 0;
	g_data.cur.cmd_count = 0;
}

char	**get_paths(void)
{
	char	*env_vars;
	char	**paths;
	char	*path_str;

	path_str = ft_strdup("PATH");
	env_vars = fetch_env_var(path_str);
	if (!env_vars)
		return (NULL);
	paths = ft_split(env_vars, ':');
	return (paths);
}

char	*find_env_var(char *str)
{
	int		word_len;
	char	*user;
	int		idx;
	int		len;

	idx = -1;
	len = ft_strlen(str);
	while (g_data.env.vars[++idx] != NULL)
	{
		if (ft_strncmp(g_data.env.vars[idx], str, len) == 0)
			break ;
	}
	word_len = ft_strlen(g_data.env.vars[idx]) - len - 1;
	user = malloc((word_len + 1) * sizeof(char));
	malloc_error_check(user);
	ft_memcpy(user, &g_data.env.vars[idx][len + 1], word_len);
	user[word_len] = '\0';
	return (user);
}
