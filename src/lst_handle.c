/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkjornra <bkjornra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:24:16 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 02:12:26 by bkjornra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	make_chain_lst(t_lst **lst, char *buf, int *idx)
{
	t_lst	*t;

	t = ft_memalloc(sizeof(t_lst));
	t->shape = ft_strdup(buf);
	put_top_left(&t->shape, PIECE_SIZE);
	t->p_sets = NULL;
	t->idx = *idx;
	t->curr = 0;
	t->n_sets = 0;
	t->next = NULL;
	t->prev = NULL;
	if (t->idx != 0)
	{
		t->prev = (*lst);
		(*lst)->next = t;
	}
	*idx += 1;
	ft_bzero(buf, 16);
	(*lst) = t;
}

int		shape_and_sets(t_lst **head, int idx)
{
	static int	call = 0;
	t_lst		*t;
	int			space;
	int			tab;

	if (call++ == 0)
	{
		space = 4;
		while (4 * idx > ft_pow(space, 2))
			space++;
	}
	else
		space = idx + 1;
	t = (*head);
	tab = call == 1 ? 4 : space - 1;
	while (IS_EXIST(t) == YES)
	{
		idx == 2 && call == 1 ? adjust_shape_for_small(&t, &space) :
			adjust_shape_by_space(&t, space, tab);
		t->n_sets = mov_amount_hrz(&t, space) * mov_amount_vtc(&t, space);
		t->p_sets = possible_sets(&t, space);
		t = t->next;
	}
	return (space);
}

char	**possible_sets(t_lst **lst, int space)
{
	char	**p_sets;
	int		horizontal;
	int		i;
	int		idx;
	char	*tmp;

	i = 0;
	idx = 0;
	horizontal = mov_amount_hrz(lst, space);
	if (!(p_sets = (char **)malloc(sizeof(char *) * ((*lst)->n_sets + 1))))
		return (NULL);
	p_sets[idx++] = ft_strdup((*lst)->shape);
	while (i < mov_amount_vtc(lst, space))
	{
		while ((tmp = ft_move(p_sets[idx - 1], 'r', space)))
		{
			p_sets[idx++] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		p_sets[idx++] = ft_move(p_sets[horizontal * i++], 'd', space);
	}
	p_sets[--idx] = (void *)0;
	return (p_sets);
}

int		mov_amount_vtc(t_lst **lst, int space)
{
	int		vtc;
	char	*shape;
	char	*temp;

	vtc = 1;
	shape = ft_strdup((*lst)->shape);
	while ((temp = ft_move(shape, 'd', space)))
	{
		ft_strdel(&shape);
		shape = ft_strdup(temp);
		ft_strdel(&temp);
		vtc++;
	}
	if (!temp)
		ft_strdel(&temp);
	ft_strdel(&shape);
	return (vtc);
}

int		mov_amount_hrz(t_lst **lst, int space)
{
	int		hrz;
	char	*shape;
	char	*temp;

	hrz = 1;
	shape = ft_strdup((*lst)->shape);
	while ((temp = ft_move(shape, 'r', space)))
	{
		ft_strdel(&shape);
		shape = ft_strdup(temp);
		ft_strdel(&temp);
		hrz++;
	}
	if (!temp)
		ft_strdel(&temp);
	ft_strdel(&shape);
	return (hrz);
}
