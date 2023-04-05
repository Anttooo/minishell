/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:43 by oanttoor          #+#    #+#             */
/*   Updated: 2023/04/05 13:05:26 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../libft/libft.h"
# include <fcntl.h>

int		parse_input(void);
char 	*get_command_path(char *token);
int 	get_cmd_count(void);
int		allocate_cmd_list(void);
int		parse_each_command(void);

#endif