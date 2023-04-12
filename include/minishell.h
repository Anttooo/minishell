/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:55 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/12 17:17:05 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	"init.h"
# include	"debug.h"
# include	"input.h"
# include	<stdio.h>
# include	"colors.h"
# include	<unistd.h>
# include	"command.h"
# include	"execute.h"
# include	"clean_exit.h"
# include 	<sys/_types.h>
# include	"signal_manager.h"
# include	"../libft/libft.h"
# include	<readline/history.h>
# include	<readline/readline.h>

typedef struct	s_sig
{
	pid_t	exec_pid;
	pid_t	shell_pid;
	pid_t	child_pid;

}								t_sig;

// struct for directory-related variables
typedef	struct	s_dir
{
	char	*builtins;
	char	*current;
	char	*home;
	char	*start;
}								t_dir;

// struct for environment-related variables
typedef struct	s_env
{
	char	*user;
	char	**vars;
	char	**paths;
	char	*prompt;
	char	*machine;
}								t_env;

// struct which contains details for one command
typedef struct  s_command
{
	char 	**args;
	char	*path;
	char 	*cmd;
}               t_cmd;

// where we store the parsed input we want to handle atm
typedef struct  s_current
{
	// something something here to hold tokens for current task
	// will execute from idx 0 -->
 	char   	*output_file;
	char	*input_file;
	t_cmd 	**cmd_list;
	int   	cmd_count;
	// added command index so that builtins can know
	// what element from **cmd_list to access
	int		cmd_index;
  	char  	*raw;
}								t_cur;

// Struct which includes all non-blank lines of input user has given
typedef	struct s_history
{
	char	**history;
	int		count;
}								t_his;

// main struct holding other structs
typedef	struct	s_data
{
	t_dir	dir;
	t_env	env;
	t_his	his;
	t_cur	cur;
	t_sig	sig;
}							  t_data;

// add functions here

#endif