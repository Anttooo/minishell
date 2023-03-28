/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_pop(void *dst, t_vec *src)
{
	if (!dst || !src)
		return (-1);
	else if (!src->memory || src->len == 0)
		return (0);
	ft_memcpy(dst, vec_get(src, src->len - 1), src->elem_size);
	src->len--;
	return (1);
}
