/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkjornra <bkjornra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:44 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 02:00:26 by bkjornra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	make_default(t_lst **t, char **ans)
{
	t_lst	*head;

	head = (*t);
	while (IS_EXIST(head))
	{
		free(head->shape);
		head->shape = ft_strdup(head->p_sets[0]);
		while (head->n_sets-- != 0)
			free(head->p_sets[head->n_sets]);
		free(head->p_sets);
		head->curr = 0;
		head = head->next;
	}
	ft_strdel(ans);
}

void	print_answer(t_lst **t, int space)
{
	char	*res;
	int		i;
	int		width;

	width = ft_pow(space, 2);
	res = ft_memalloc(width + 1);
	while ((*t)->prev)
		(*t) = (*t)->prev;
	while ((i = -1) && IS_EXIST((*t)) == YES)
	{
		while (++i < width)
			if ((*t)->p_sets[(*t)->curr][i] == '1')
				res[i] = (*t)->idx + 'A';
		(*t) = (*t)->next;
	}
	while (++i < width)
		if (IS_EXIST(res[i]) == NO)
			res[i] = '.';
	pretty_printer(res, space);
	ft_strdel(&res);
}

void	pretty_printer(char *res, int space)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < space)
	{
		temp = ft_strsub(res, i * space, space);
		ft_putendl(temp);
		ft_strdel(&temp);
	}
}

int		print_error(void)
{
	ft_putstr("error\n");
	return (1);
}

void	freeing_whole_lst(t_lst **lst)
{
	int		i;
	t_lst	*t;

	while ((*lst))
	{
		t = (*lst);
		(*lst) = t->next;
		free(t->shape);
		i = 0;
		while (t->p_sets[i])
			free(t->p_sets[i++]);
		free(t->p_sets);
		free(t);
	}
}
