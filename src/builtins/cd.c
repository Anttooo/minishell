/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:57:54 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 17:20:32 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

void	ft_cd(void)
{
	char	*target;

	target = ft_strdup(g_data.cur.cmd_list[g_data.cur.cmd_index]->args[1]);
	if (closedir(g_data.dir.ptr_current) != 0)
		printf("close dir failed \n");
	g_data.dir.ptr_current = opendir(target);
	if (!g_data.dir.ptr_current)
		printf("open dir failed \n");
	if (chdir(target) != 0)
		printf("change dir failed \n");
	g_data.dir.current = getcwd(g_data.dir.current, 1024);
	free(target);
}
