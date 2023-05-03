/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/03 12:31:28 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/libft.h"

# define DEFAULT_MODE 1
# define DOUBLE_QUOTES_MODE 2
# define SINGLE_QUOTES_MODE 3
# define EXPANSION_MODE 4

int		handle_input(char *input);
int	tokenize_input(void);
int	is_terminating_char(char c, int *mode);
void  store_token(void);
void 	store_current_token(void);
void  add_char_to_buffer(char c);
void  empty_and_init_buffer(void);
int	evaluate_char(char	c, int *mode, int i);
int is_stored_char(char c, int *mode);
int	is_trigger_char(char c, int	*mode);
int	is_mode_changing_char(char c, int *mode);

#endif