/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:49:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/06 16:33:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include <stdlib.h>

#include "libft.h"
#include "printable.h"

t_list *new_printable();
t_list	*read_format_string(const char *format);
int	read_placeholder(const char **format, t_list *printables);

void put_printable(t_list *printable);

#endif