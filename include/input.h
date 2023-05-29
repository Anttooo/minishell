/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/25 12:41:58 by oanttoor         ###   ########.fr       */
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


#endif