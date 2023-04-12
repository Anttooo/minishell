/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:14:42 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/04/12 13:57:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Define regular font colors
# define regularRed "\033[0;31m"
# define regularGreen "\033[0;32m"
# define regularYellow "\033[0;33m"
# define regularBlue "\033[0;34m"
# define regularPurple "\033[0;35m"
# define regularCyan "\033[0;36m"
# define regularWhite "\033[0;37m"

// Define bold font colors
# define boldRed "\033[1;31m"
# define boldGreen "\033[1;32m"
# define boldYellow "\033[1;33m"
# define boldBlue "\033[1;34m"
# define boldPurple "\033[1;35m"
# define boldCyan "\033[1;36m"

# define resetColor "\033[0m"

void	reset_color(void);
void	change_color(char *color, int type);

#endif