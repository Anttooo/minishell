/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:58 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 14:12:04 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"

# define DEFAULT 0
# define WITHIN_QUOTES 1
# define DEFAULT_MODE 1
# define DOUBLE_QUOTES_MODE 2
# define SINGLE_QUOTES_MODE 3
# define HEREDOC_MODE 4
# define EXPANSION_MODE_DEFAULT 11
# define EXPANSION_MODE_DOUBLE_Q 12

// Expansion mode
void	handle_expansion_mode(int *mode, int *i);
int		is_valid_subsequent_character(char c);
int		is_valid_first_character(char c);
char	*fetch_env_var(char *str);
int		is_exit_status_expansion(int j);

// Edge cases
int		is_edge_case(char c, char next_c, int *mode, int *i);
int		handle_within_quotes(char c, char next_c, int *i);
int		handle_default_mode(char c, char next_c, int *i);
int		is_double_greater_than(char c, char next_c);
int		is_smaller_than(char c);
int		is_greater_than(char c);

// Buffer handling
void	handle_double_greater_than(int *i);
void	clear_and_init_buffer(void);
void	add_char_to_buffer(char c);

// Store token
void	add_double_greater_than_within_quotes(int *i);
void	store_token_within_quotes(void);
void	add_char_within_quotes(char c);
void	store_current_token(void);
void	store_current_token_within_quotes(void);
void	store_token(void);
void	store_empty_token(void);

// Char evaluation
int		evaluate_char(char c, int *mode, int *i);
int		is_mode_changing_char(char c, int *mode);
int		is_trigger_char(char c, int	*mode);
int		is_stored_char(char c, int *mode);

int		is_terminating_char(char c, int *mode);
int		needs_blanc(char c, int *mode);
int		tokenize_input(void);

#endif