/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:49 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 18:17:58 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data	g_data;

// Tokenize input
// stores the last token once the input string ends
int	tokenize_input(void)
{
	int	idx;
	int	mode;

	idx = 0;
	mode = DEFAULT_MODE;
	vec_new(&g_data.cur.tokens, 0, sizeof(char *));
	vec_new(&g_data.cur.types, 0, sizeof(int));
	vec_new(&g_data.cur.token_buffer, 0, sizeof(char));
	while (g_data.cur.raw[idx] != '\0')
	{
		evaluate_char(g_data.cur.raw[idx], &mode, &idx);
		if (mode > 10)
			handle_expansion_mode(&mode, &idx);
		idx++;
	}
	store_token();
	return (0);
}
