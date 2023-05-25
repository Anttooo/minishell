/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 09:59:04 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;

void	add_double_greater_than_within_quotes(int *i)
{
	handle_double_greater_than(i);
	store_token_within_quotes();
}

void	add_char_within_quotes(char c)
{
	ft_printf("test 1\n");
	add_char_to_buffer(c);
	store_token_within_quotes();
}

int is_greater_than(char c)
{
    return (c == '>');
}

int is_smaller_than(char c)
{
	return (c == '<');
}

int	is_double_greater_than(char c, char next_c)
{
    return (c == '>' && next_c == '>');
}