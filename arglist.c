/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:56:44 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/10 12:00:37 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

// Two potential memory leaks int the next two functions due to not freeing the argument array
static int	expand_arglist(t_arglist *arglist, int new_size)
{
	t_argument **tmp;

	if (new_size <= arglist->size)
		return (1);
	tmp = arglist->args;
	arglist->args = (t_argument **)malloc(new_size * sizeof(t_argument *));
	if (arglist->args == NULL)
		return (0);
	ft_bzero(arglist->args, new_size * sizeof(t_argument *));
	ft_memcpy(arglist->args, tmp, arglist->size * sizeof(t_argument *));
	if (tmp)
		free(tmp);
	arglist->size = new_size;
	return (1);
}

static int	set_arg_type(t_arglist *arglist, int index, ARGSIZE type)
{
	t_argument *arg;

	if (arglist == NULL || index < 1)
		return (0);
	if (index > arglist->size)
		if (!expand_arglist(arglist, index))
			return (0);
	if (arglist->args[index - 1] == NULL)
	{
		arglist->args[index - 1] = (t_argument *)malloc(sizeof(t_argument));
		if (arglist->args[index - 1] == NULL)
			return (0);
	}
	arg = arglist->args[index - 1];
	arg->type = type;
	arg->data = NULL;
	return (1);
}

static t_arglist	*new_arglist(void)
{
	t_arglist *arglist;

	arglist = (t_arglist *)malloc(sizeof(t_arglist));
	if (arglist == NULL)
		return (NULL);
	arglist->args = 0;
	arglist->size = 0;
	return (arglist);
}

static int	parse_args_positional(t_arglist *arglist, t_printable *p)
{
	ARGSIZE size;

	if (p->field_width_arg != -1)
		if (!set_arg_type(arglist, p->field_width_arg, SIZE_INT))
			return (0);
	if (p->precision_arg != -1)
		if (!set_arg_type(arglist, p->precision_arg, SIZE_INT))
			return (0);
	if (p->data_arg != -1)
	{
		size = size_of_type(p->type, p->modifier);
		if (!set_arg_type(arglist, p->data_arg, size))
			return (0);
	}
	return (1);
}

static int	parse_args(t_arglist *arglist, t_printable *p)
{
	ARGSIZE size;

	if (p->field_width_arg == 0)
		if (!set_arg_type(arglist, arglist->size + 1, SIZE_INT))
			return (0);
	if (p->precision_arg == 0)
		if (!set_arg_type(arglist, arglist->size + 1, SIZE_INT))
			return (0);
	if (p->data_arg == 0)
	{
		size = size_of_type(p->type, p->modifier);
		if (!set_arg_type(arglist, arglist->size + 1, size))
			return (0);
	}
	return (1);
}

t_arglist	*build_arglist(t_list *printables, int positional)
{
	t_arglist	*arglist;
	t_printable	*p;

	arglist = new_arglist();
	if (arglist == NULL)
		return (NULL);
	while (printables)
	{
		p = (t_printable *)printables->content;
		if (p)
		{
			if (positional)
			{
				if (!parse_args_positional(arglist, p))
					return (NULL);
			}
			else if (!parse_args(arglist, p))
				return (NULL);
		}
		printables = printables->next;
	}
	return (arglist);
}

void	free_arglist(t_arglist **arglist)
{
	int			i;
	t_argument	**args;

	i = 0;
	if ((arglist == NULL) || (*arglist == NULL))
		return ;
	args = (*arglist)->args;
	while (i < (*arglist)->size)
	{
		if (args[i])
		{
			if (args[i]->data)
				free(args[i]->data);
			free(args[i]);
		}
		i++;
	}
	free(args);
	free(*arglist);
	*arglist = NULL;
}
