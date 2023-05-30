/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:06 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/05/30 16:37:56 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
# define SIGNAL_MANAGER_H

# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>

void	signal_manager(void);

#endif