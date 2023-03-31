/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/31 10:26:38 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

// TODO:
// Input will be options(maybe) and arguments to print
// needs to scan for $wildcard character to possibly print from variable
// this is probalby easist to be done if args are printed one by one and if stumble upon wildcard
// enter a loop to print that, and then return to main loop printing args one by one.
void	echo(int argc, char	**argv)
{
	
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		echo(argc, argv);
	return (0);
}