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

#include "pwd.h"

// TODO: Figure out why it takes more than this, it cant be this easy
// pwd program only takes in current_dir variable from main program and prints it out.
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		return (1);
	}
	return (-1);
}