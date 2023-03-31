/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/31 07:24:42 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	main(int argc, char **argv)
{
	// printf("Using builtin function. \n");
	
	// export should print out the list of environment variables.
	// During the initialisation of the program, all existing environment variables are added to g_data.env.vars
	// and then that list is updated while the shell is running. Therefore, it should be enough to just print out 
	// the list in g_data.env.vars for export. That list is given through argv I suppose.
	int	i;

	i = 1; 
	while(argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
}