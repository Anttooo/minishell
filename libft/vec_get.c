/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/05/25 10:49:50 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*vec_get(t_vec *src, size_t index)
{
	unsigned char	*ptr;

	if (index >= src->len || !src || !src->memory)
		return (NULL);
	ptr = &src->memory[src->elem_size * index];
	return (ptr);
}
