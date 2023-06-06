/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:10:30 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 14:12:04 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/input.h"
#include "../../include/command.h"
#include "../../include/minishell.h"

extern t_data g_data;

int	heredoc_start_index(char *input)
{
	int	i;
	int	mode;

	i = 0;
	mode = DEFAULT_MODE;
	while (input[i] != '\0')
	{
		is_mode_changing_char(input[i], &mode);
		if (input[i] == '<' && input[i + 1] == '<' && mode == DEFAULT_MODE)
			return (i);
		i++;
	}
	return (-1);
}

int	get_delim_start_index(char *input, int heredoc_start_idx)
{
	int	delim_start_idx;
	int	i;

	i = heredoc_start_idx;
	while (input[i] && input[i] != '\0' && ft_isalpha(input[i]) == 0)
		i++;
	delim_start_idx = i;
	printf("Delim start idx: %d\n", delim_start_idx);
	return (delim_start_idx);
}

int	get_delim_end_index(char *input, int delim_start_idx)
{
	int	delim_end_idx;
	int	i;

	i = delim_start_idx;
	while (ft_isalnum(input[i]) == 1  && input[i] != '\0')
		i++;
	delim_end_idx = i;
	printf("Delim end idx: %d\n", delim_end_idx);
	return (delim_end_idx);
}

char	*heredoc_delim(char *input, int heredoc_start_idx)
{
	char	*delim;
	int		delim_start_idx;
	int		delim_end_idx;
	int		delim_len;

	delim_start_idx = get_delim_start_index(input, heredoc_start_idx);
	delim_end_idx = get_delim_end_index(input, delim_start_idx);
	delim_len = delim_end_idx - delim_start_idx;
	delim = ft_substr(input, delim_start_idx, delim_len);
	return (delim);
}