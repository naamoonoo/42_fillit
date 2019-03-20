/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:24:16 by hnam              #+#    #+#             */
/*   Updated: 2019/03/19 23:24:17 by hnam             ###   ########.fr       */
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
	static int 	call = 0;
	t_lst 		*t;
	int			space;
	
	if (call++ == 0)
	{
		space = 4;
		while (4 * idx > ft_pow(space, 2))
			space++;
	}
	else
		space = idx + 1;
	t = (*head);
	while (IS_EXIST(t) == YES)
	{
		idx == 2 && call == 1 ? 
			adjust_shape_for_small(&t, &space) : 
			adjust_shape_by_space(&t, space, call == 1 ? 4 : space - 1);
		t->n_sets = (mov_amount_horizon(&t, space) * 
			mov_amount_vertical(&t, space));
		t->p_sets = possilbe_sets(&t, space);
		t = t->next;
	}
	return (space);
}

char 	**possilbe_sets(t_lst **lst, int space)
{
	char	**p_sets;
	int		horizontal;
	int		vertical;
	int		i;
	int		idx;
	char	*tmp;

	i = 0;
	idx = 0;
	horizontal = mov_amount_horizon(lst, space);
	vertical = mov_amount_vertical(lst, space);
	if(!(p_sets = (char **)malloc(sizeof(char *) * ((*lst)->n_sets + 1))))
		return (NULL);
	p_sets[idx++] = ft_strdup((*lst)->shape);
	while (i < vertical)
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

int		mov_amount_vertical(t_lst **lst, int space)
{
	int vtc;
	char *shape;
	char *temp;

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

int		mov_amount_horizon(t_lst **lst, int space)
{
	int hrz;
	char *shape;
	char *temp;

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
