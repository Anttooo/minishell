/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oanttoor <oanttoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:46:09 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/06 15:44:05 by oanttoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKING_H
# define ERROR_CHECKING_H

# include <errno.h>

void	malloc_error_check(char *string);
void	string_array_malloc_error_check(char **string);

#endif