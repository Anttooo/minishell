/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:07:29 by jmykkane          #+#    #+#             */
/*   Updated: 2023/03/29 11:16:00 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_list)
{
	t_list	*curr;

	if (new_list)
	{
		if (*lst == NULL)
			*lst = new_list;
		else
		{
			curr = *lst;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = new_list;
		}
	}
}
