/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/25 11:11:48 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include <signal.h>
# include <dirent.h>
# include "minishell.h"

void	ft_cd(void);
void	ft_pwd(void);
void	ft_env(void);
void	ft_echo(void);
void	ft_exit(void);
void	ft_unset(void);
void	ft_export(void);

#endif