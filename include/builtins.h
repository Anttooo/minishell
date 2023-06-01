/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 19:26:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <signal.h>
# include <dirent.h>

void	ft_cd(void);
void	ft_pwd(void);
void	ft_env(void);
void	ft_echo(void);
void	ft_exit(void);
void	ft_unset(int cmd_idx);
void	ft_export(int cmd_idx);

// Helpers for export and unset
int		get_env_var_count(void);
void	free_env_vars(void);

#endif