/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/05 14:13:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <signal.h>
# include <dirent.h>

int		ft_cd(void);
int		ft_pwd(void);
int		ft_env(void);
int		ft_echo(int cmd_index);
void	ft_exit(void);
int		ft_unset(int cmd_idx);
int		ft_export(int cmd_idx);

// Helpers for export and unset
int		get_env_var_count(void);
void	free_env_vars(void);
int		arr_len(void);

#endif