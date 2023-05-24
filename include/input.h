/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/24 14:16:41 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../libft/libft.h"

# define DEFAULT_MODE 1
# define DOUBLE_QUOTES_MODE 2
# define SINGLE_QUOTES_MODE 3
# define EXPANSION_MODE_DEFAULT 11
# define EXPANSION_MODE_DOUBLE_Q 12

void	store_token(void);
int		tokenize_input(void);
int		is_smaller_than(char c);
int		is_greater_than(char c);
void 	store_current_token(void);
char	*fetch_env_var(char *str);
int		handle_input(char *input);
void	add_char_to_buffer(char c);
void	empty_and_init_buffer(void);
void	clear_and_init_buffer(void);
void	add_char_with_quotes(char c);
int		is_stored_char(char c, int *mode);
void	handle_double_greater_than(int *i);
int		is_trigger_char(char c, int	*mode);
int		is_mode_changing_char(char c, int *mode);
void	handle_expansion_mode(int *mode, int *i);
int		evaluate_char(char	c, int *mode, int *i);
void	add_double_greater_than_with_quotes(int *i);
int		is_double_greater_than(char c, char next_c);
int		is_terminating_char(char c, char next_c, int *mode);

#endif