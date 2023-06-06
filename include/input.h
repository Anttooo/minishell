/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 19:01:31 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/libft.h"

int		handle_input(char *input);
int		is_multiline(char *input);
char	*handle_heredoc(char **input);
void	handle_multiline(char **input);
int		heredoc_start_index(char *input);
char	*update_buffer(char *buffer, char *new_input);
char	*handle_unclosed_quote(char *input, int mode);
char	*heredoc_delim(char *input, int heredoc_start_idx);
int		get_delim_end_index(char *input, int delim_start_idx);
void	heredoc_free_part_a_and_b(char **part_a, char **part_b);
int		get_delim_start_index(char *input, int heredoc_start_idx);
char	*combine_input_and_multiline_buffer(char	*input, char *buffer);

#endif