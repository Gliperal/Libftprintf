/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:02:45 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/08 16:03:37 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
// TODO Remove
#include <stdio.h>

static int read_text(const char **format, t_list *printables)
{
	const char *start;
	t_list *elem;
	t_printable *p;

	start = *format;
	while (**format != '%' && **format != 0)
		*format = *format + 1;
	elem = new_printable();
	if (elem == NULL)
		return (-1);
	p = (t_printable *)elem->content;
	p->type = 's';
	p->precision = *format - start;
	p->data = (char *)*format;
	ft_lstappend(printables, elem);
	return (0);
}

t_list	*read_format_string(const char *format)
{
	t_list *printables;
	int status;
	const char **str;

	printables = ft_lstnew(0, 0);
	if (printables == NULL)
		return (NULL);
	str = &format;
	while (**str != 0)
	{
		if (**str == '%')
			status = read_placeholder(str, printables);
		else
			status = read_text(str, printables);
		if (status == -1)
		{
			// TODO ft_lstdel(&printables, );
			return (NULL);
		}
	}
	return (printables);
}
