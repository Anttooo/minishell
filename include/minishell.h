/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:44:55 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 16:59:24 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include	"init.h"
# include	"debug.h"
# include	"input.h"
# include	"tokenizer.h"
# include	<stdio.h>
# include	"colors.h"
# include	<unistd.h>
# include	"command.h"
# include	"execute.h"
# include	"builtins.h"
# include	"clean_exit.h"
# include	"signal_manager.h"
# include	<readline/history.h>
# include	<readline/readline.h>

#endif