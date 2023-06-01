/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:57:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 16:00:39 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

static int	open_and_close(char *target)
{
	if (!g_data.dir.ptr_target)
	{
		perror("shell: cd: ");
		free(target);
		return (1);
	}
	if (closedir(g_data.dir.ptr_current) != 0)
	{
		perror("closedir function failed \n");
		clean_exit_shell();		
	}
	if (chdir(target) != 0)
	{
		perror("chdir function failed \n");
		clean_exit_shell();		
	}
	free(target);
	return (0);
}

void	ft_cd(void)
{
	char	*target;
	int		len;

	len = arr_len();
	if (len > 1)
	{
		target = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[1]);
		g_data.dir.ptr_target = opendir(target);
		if (open_and_close(target) == 1)
			return ;
		g_data.dir.current = getcwd(g_data.dir.current, 1024);
		g_data.dir.ptr_current = g_data.dir.ptr_target;
	}
}
