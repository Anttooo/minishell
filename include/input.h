/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 14:12:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/libft.h"

int		handle_input(char *input);
int		is_multiline(char *input);
void	handle_multiline(char **input);
char	*handle_unclosed_quote(char *input, int mode);
char	*combine_input_and_multiline_buffer(char	*input, char *buffer);
char	*update_buffer(char *buffer, char *new_input);
char	*handle_heredoc(char **input);
int		heredoc_start_index(char *input);
int		get_delim_start_index(char *input, int heredoc_start_idx);
int		get_delim_end_index(char *input, int delim_start_idx);
char	*heredoc_delim(char *input, int heredoc_start_idx);

#endif