/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/06 17:57:24 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define EXPORT 1
# define SHELL 2

# include "minishell.h"
# include <signal.h>
# include <dirent.h>

// Builtin functions
int		ft_cd(void);
int		ft_pwd(void);
int		ft_env(void);
void	ft_exit(void);
int		ft_export(int cmd_idx);
int		ft_echo(int cmd_index);
int		ft_unset(int cmd_idx, int caller);

// Helpers for builtins
int		arr_len(void);
int		ft_isnum(int c);
void	free_env_vars(void);
int		is_env_var(char *arg);
int		get_env_var_count(void);
int		get_env_var_count(void);
int		ft_isvalid_int(char *str);
char	*extract_until_equal(char *arg);

#endif