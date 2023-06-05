/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builltin_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:11:12 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 14:37:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

extern t_data	g_data;

int	arr_len(void)
{
	int	idx;

	idx = 0;
	if (g_data.cur.cmd_list == NULL)
		return (1);
	while (g_data.cur.cmd_list[g_data.cur.cmd_index]->args[idx] != NULL)
		idx++;
	return (idx);
}
