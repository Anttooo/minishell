#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include	<sys/_types.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct s_sig
{
	pid_t	exec_pid;
	pid_t	shell_pid;
	pid_t	child_pid;
}								t_sig;

// struct for directory-related variables
typedef struct s_dir
{
	char	*builtins[7];
	char	*current;
	char	*home;
	char	*start;

	DIR		*ptr_home;
	DIR		*ptr_start;
	DIR		*ptr_current;
}								t_dir;

// struct for environment-related variables
typedef struct s_env
{
	char	*user;
	char	**vars;
	char	**paths;
	char	*prompt;
	char	*machine;
}								t_env;

// struct which contains details for one command
// If path = "builtin" 
typedef struct s_command
{
	char	*output;
	char	*input;
	int		output_mode;
	int		builtin;
	char	**args;
	char	*cmd;
}								t_cmd;

typedef struct s_token
{
	char	*token;
	int		type;
}								t_token;

// where we store the parsed input we want to handle atm
typedef struct s_current
{
	t_cmd	**cmd_list;
	int		cmd_count;
	int		cmd_index;
	char	*output;
	int		output_mode;
	char	*input;
	char	*raw;
	t_vec	types;
	t_vec	tokens;
	t_vec	token_buffer;
	int		err_flag;
	int		heredoc_flag;
}								t_cur;

// Struct which includes all non-blank lines of input user has given
typedef struct s_history
{
	char	**history;
	int		count;
}								t_his;

// main struct holding other structs
typedef struct s_data
{
	t_dir	dir;
	t_env	env;
	t_his	his;
	t_cur	cur;
	t_sig	sig;
}								t_data;

#endif