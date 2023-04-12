/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:21:15 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/12 13:57:36 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/colors.h"
#include "../libft/libft.h"

void	reset_color(void)
{
	printf(regularWhite);
	
}

static void	regular(char *color, int len)
{
	if (ft_strncmp("RED", color, len) == 0)
		printf(regularRed);
	else if (ft_strncmp("GREEN", color, len) == 0)
		printf(regularGreen);
	else if (ft_strncmp("BLUE", color, len) == 0)
		printf(regularBlue);
	else if (ft_strncmp("YELLOW", color, len) == 0)
		printf(regularYellow);
	else if (ft_strncmp("CYAN", color, len) == 0)
		printf(regularCyan);
	else if (ft_strncmp("PURPLE", color, len) == 0)
		printf(regularPurple);
}

static void	bold(char *color, int len)
{
	if (ft_strncmp("RED", color, len) == 0)
		printf(boldRed);
	else if (ft_strncmp("GREEN", color, len) == 0)
		printf(boldGreen);
	else if (ft_strncmp("BLUE", color, len) == 0)
		printf(boldBlue);
	else if (ft_strncmp("YELLOW", color, len) == 0)
		printf(boldYellow);
	else if (ft_strncmp("CYAN", color, len) == 0)
		printf(boldCyan);
	else if (ft_strncmp("PURPLE", color, len) == 0)
		printf(boldPurple);
}

void	change_color(char *color, int type)
{
	int	len;

	len = ft_strlen(color);
	if (type == 0)
	{
		regular(color, len);
	}
	else if (type == 1)
	{
		bold(color, len);
	}
	else
	{
		printf("Error in colors \n");
	}
}