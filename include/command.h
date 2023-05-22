/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/05/17 16:30:35 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../libft/libft.h"
# include <fcntl.h>

# define INPUT_REDIR 	2
# define OUTPUT_REDIR	3
# define APPEND_MODE 	1
# define OVERWRITE_MODE 2

int 	get_cmd_count(void);
int		parse_commands(void);
int   	tokenize_input(void);
int		allocate_cmd_list(void);
void		parse_single_cmd(int cmd_idx, int *token_idx);
int		is_delim_token(int i);
char 	*get_command_path(char *token);

#endif