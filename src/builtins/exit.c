/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:49:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/31 17:52:11 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	arr_len(void)
{
	int	idx;

	idx = 0;
	while (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[idx] != NULL)
		idx++;
	return (idx);
}

// static char	*build_str(void)
// {
// 	char	*str;

// 	return (str);
// }

void	ft_exit(void)
{
	int		status;
	char	*arg;
	int		len;

	status = 0;
	len = arr_len();
	printf("exit\n");
	if (len > 1)
	{
		arg = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[1]);
		if (ft_isalnum(arg) == 0)
		{
			status = ft_atoi(arg);
			free(arg);
			if (len == 2)
			{
				clean_exit_shell();
				exit(status);
			}
			ft_putstr_fd("shell: exit: too many arguments\n", 2);
			exit(status);
		}
		ft_putstr_fd("shell: exit: numeric argument required\n", 2);
	}
	exit(status);
}
