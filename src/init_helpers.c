/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:13:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/12 14:17:19 by joonasmykka      ###   ########.fr       */
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
	if (!user)
		return (NULL);
	ft_memcpy(user, &g_data.env.vars[idx][len + 1], word_len);
	user[word_len] = '\0';
	return (user);
}