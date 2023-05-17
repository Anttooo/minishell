// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   command.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
// /*   Updated: 2023/05/17 16:51:28 by joonasmykka      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/command.h"
// #include "../include/minishell.h"
// #include "../include/debug.h"

// extern t_data	g_data;


// // Parse input takes in a perfect list of tokens and creates perfect command structs that can be passed to execute
// int	parse_commands(void)
// {
// 	// this is not needed after tokinzer is compele, it will pass on token list.
// 	// ***** Delete starts here ******
// 	char	**tokens;
// 	tokens = ft_split(g_data.cur.raw, ' '); // TODO: replace this will tokenize.c tokenizing
// 	if (!tokens || tokens == NULL) // TODO: move this somewhere where it makes more sense to notice that there are no tokens
// 		return (-1);
	
// 	/*
// 		g_data.cur.vec_tokens
// 			vec_tokens[0].token = cat
// 			vec_tokens[1].token = file1
// 			vec_tokens[2].token = |
// 			vec_tokens[3].token = sort
// 	*/

// 	// ****** Delete ends here ********

// 	get_cmd_count(); // 2 commands
// 	allocate_cmd_list(); // array with 2 t_cmd instances
// 	parse_each_command(); // fills t_cmd struct with proper tokens

// 	// What happens below is filling cmd, path, and args for each command
// 	// in their own structs
// 	// ******* THIS PART IS REPLACED WITH PARSE EACH COMMAND ******
// 	// go through each command and store the things related to them in the struct
//     // store the command
// 	// This is kinda what the parse_each_command should be doing but in a loop for each command
// 	g_data.cur.cmd_list[0]->cmd = ft_strdup(tokens[0]);
// 	g_data.cur.cmd_list[0]->path = ft_strdup(get_command_path(tokens[0]));
// 		if (!g_data.cur.cmd_list[0]->path)
// 		return (-1);
// 	// TODO: if the command can't be found, command_path is null and error should be given
	
// 	g_data.cur.cmd_list[0]->args = ft_split(g_data.cur.raw, ' ');

// 	// ****** REPLACED PART ENDS *******
// 	return (0);
// }

// int get_cmd_count(void)
// {
//   // start from the beginning of the command, go character by character looking for pipes
//   int 	i;
//   int 	count;
//   char  skip_char;

//   i = 0;
//   count = 1;
//   while(g_data.cur.raw[i] != '\0')
//   {
//     if(g_data.cur.raw[i] == '|')
//     {
//       count++;
//     }
//     // if there is a single or double quote, skip until the same character is seen again
//     if(g_data.cur.raw[i] == '\"' || g_data.cur.raw[i] == '\'')
//     {
//       skip_char = g_data.cur.raw[i];
//       i++;
//       while(g_data.cur.raw[i] != skip_char && g_data.cur.raw[i] != '\0')
//         i++;
//     }
//     i++;
//   }
//   g_data.cur.cmd_count = count;
// //   ft_printf("nr of commands: %d\n", g_data.cur.cmd_count);
//   return (0);
// }


// // This command will parse together e.g. arguments for a single command
// // After this, we should have the final command struct for each command
// int	parse_each_command(void)
// {
// 	// If we see a redirection, handle setting the values in g_data.cur.input_file/output_file
// 	return (0);	
// }

// int	is_builtin(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 7)
// 	{
// 		if (ft_strncmp(cmd, g_data.dir.builtins[i],10) == 0)
// 		{
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// char *get_command_path(char *token)
// {
// 	int		i;
// 	char	*cmd_path;
// 	char	*path_with_slash;

// 	// TODO: restructure this code to check from an array of possible builtins, this code is invalid
// 	if(is_builtin(token) == 0)
// 	{
// 		printf("Command is a builtin\n");
// 		return("builtin");
// 	}
// 	i = 0;
// 	while (g_data.env.paths[i])
// 	{
// 		path_with_slash = ft_strjoin(g_data.env.paths[i], "/");
// 		cmd_path = ft_strjoin(path_with_slash, token);
// 		if(access(cmd_path, X_OK) == 0) 
		
// 			// printf("Command is an environment command, can be executed\n");
// 			return (cmd_path);
// 		}
// 		free(path_with_slash);
// 		free(cmd_path);
// 		i++;	
// 	}
// 	printf("command not found\n");
// 	return(NULL);
// }