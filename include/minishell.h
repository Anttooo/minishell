/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:55 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/31 12:35:37 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// struct for directory-related variables
typedef	struct	s_dir
{
	char	*current;
	char	*start;
	char	*home;
	char	*builtins;
}								t_dir;

// struct for environment-related variables
typedef struct	s_env
{
	char	**vars;
	char	**paths;
}								t_env;

// main struct holding other structs
typedef	struct	s_data
{
  t_dir	dir;
  t_env	env;
}								t_data;

# include "debug.h"

# include <stdio.h>
# include "execute.h"
# include "input.h"
# include "execute.h"
# include "command.h"
# include	"init.h"
# include "clean_exit.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

// add functions here

#endif