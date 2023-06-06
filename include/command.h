/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/25 13:36:52 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../libft/libft.h"
# include <fcntl.h>
# include "types.h"
# include "minishell.h"

# define INPUT_REDIR 	2
# define OUTPUT_REDIR_OVERWRITE	3
# define OUTPUT_REDIR_APPEND	4
# define APPEND_MODE 	1
# define OVERWRITE_MODE 2

int				is_delim(int i);
int				get_cmd_count(void);
int				parse_commands(void);
int				tokenize_input(void);
int				is_builtin(char *cmd);
int             parser_allocate(int i);
int				allocate_cmd_list(void);
t_token			*get_token(int token_idx);
void			parse_single_cmd(int cmd_idx, int *token_idx);
int				check_mode(char *token, int type, int cmd_idx);
void			handle_cmd(int cmd_idx, char *token, int *args_index);
void			handle_args(int cmd_idx, char *token, int *args_index);
int				handle_input_redirection(int cmd_idx, char *token, int *mode);
void			handle_cmd_and_args(int cmd_idx, char *token, int *args_index);
int				handle_output_redirection(int cmd_idx, char *token, int *mode);

#endif