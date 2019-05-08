/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:28:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/08 16:04:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO into header files
#include <stdarg.h>
void		extract_args(t_list *printables, va_list *ap);
t_list	*read_format_string(const char *format);

int	ft_printf(const char *format, ...)
{
	t_list *printables;

	printables = read_format_string(format);
	extract_args(printables, 0);
	return (0);
}
