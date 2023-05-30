/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:26:08 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 18:26:20 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

void	debug_print_list(char	**list, const char *func_name);
void	debug_print_string(char *string, const char *func_name);
void	debug_print_tokens(void);
void	debug_print_commands(void);

#endif