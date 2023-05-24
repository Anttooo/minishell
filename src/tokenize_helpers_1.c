/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helpers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/24 13:53:25 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/input.h"
#include "../include/command.h"
#include "../include/minishell.h"

extern	t_data g_data;

void	add_double_greater_than_with_quotes(int *i)
{
	add_char_to_buffer('\"');
	handle_double_greater_than(i);
	add_char_to_buffer('\"');
	store_token();
}

void	add_char_with_quotes(char c)
{
	add_char_to_buffer('\"');
	add_char_to_buffer(c);
	add_char_to_buffer('\"');
	store_token();
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