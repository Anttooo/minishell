/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:38:38 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/03/30 11:43:54 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

// pwd program only takes in current_dir variable from main program and prints it out.
int	main(int argc, char **argv)
{
	printf("%d\n", argv[1]);
	return (0);
}