/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:55 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/30 10:43:46 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


// struct for directory-related variables
typedef	struct	s_dir
{
	char	*dir_current;
  char	*dir_home;
}								t_dir;


// struct for environment-related variables
typedef struct	s_env
{
	char	**paths;
}								t_env;

// main struct holding other structs
typedef	struct	s_data
{
  t_dir	dir;
  t_env	env;
}					t_data;

# include "debug.h"

# include <stdio.h>
# include "execute.h"
# include "input.h"
# include "execute.h"
# include "command.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

// add functions here 

#endif