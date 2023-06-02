/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:09 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/01 16:05:20 by joonasmykka      ###   ########.fr       */
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
int		arr_len(void);
void	ft_unset(void);
void	ft_export(void);

#endif