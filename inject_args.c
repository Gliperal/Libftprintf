/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:53:28 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 12:57:17 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	parse_args(t_printable *p, t_arglist *arglist)
{
	t_argument	*arg;

	if (p->field_width_arg == 0)
	{
		arg = arglist->args[arglist->index];
		p->field_width = *((int *)arg->data);
		arglist->index++;
	}
	if (p->precision_arg == 0)
	{
		arg = arglist->args[arglist->index];
		p->precision = *((int *)arg->data);
		arglist->index++;
	}
	if (p->data_arg == 0)
	{
		arg = arglist->args[arglist->index];
		p->data = arg->data;
		arglist->index++;
	}
}

static void	parse_args_positional(t_printable *p, t_arglist *arglist)
{
	t_argument	*arg;

	if (p->field_width_arg != -1)
	{
		arg = arglist->args[p->field_width_arg - 1];
		p->field_width = *((int *)arg->data);
	}
	if (p->precision_arg != -1)
	{
		arg = arglist->args[p->precision_arg - 1];
		p->precision = *((int *)arg->data);
	}
	if (p->data_arg != -1)
	{
		arg = arglist->args[p->data_arg - 1];
		p->data = arg->data;
	}
}

void		inject_args(t_list *printables, t_arglist *arglist, int positional)
{
	t_printable	*p;

	arglist->index = 0;
	while (printables)
	{
		p = (t_printable *)printables->content;
		if (p)
		{
			if (positional)
				parse_args_positional(p, arglist);
			else
				parse_args(p, arglist);
		}
		printables = printables->next;
	}
}
