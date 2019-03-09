#include "fillit.h"

t_lst	*make_chain_lst(t_lst **head, t_lst **lst, char *buf, int *idx)
{
	t_lst	*t;

	if(!(t = malloc(sizeof(t_lst))))
		return (0);
	t->shape = ft_strdup(buf);
	t->p_sets = NULL;
	t->idx = *idx;
	t->curr = 0;
	t->n_sets = 0;
	t->next = NULL;
	if (*idx == 0)
	{
		t->prev = NULL;
		(*head) = t;
	}
	else
	{
		t->prev = (*lst);
		(*lst)->next = t;
	}
	*idx += 1;
	ft_memset(buf, 0, 16);
	return (t);
}

int		shape_and_sets(t_lst **head, int idx)
{
	t_lst 	*t;
	int		space;
	
	space = 4;
	while (4 * idx > ft_pow(space, 2))
		space++;
	t = (*head);
	while(IS_EXIST(t) == YES)
	{
		adjust_shape_by_space(&t, space);
		while(IS_EXIST(ft_move(t->shape, 'u', space)) == YES)
			t->shape = ft_move(t->shape, 'u', space);
		while(IS_EXIST(ft_move(t->shape, 'l', space)) == YES)
			t->shape = ft_move(t->shape, 'l', space);
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

	if(!(p_sets = (char **)malloc(sizeof(char *) * (mov_amount(lst, 't', space) + 1))))
		return (NULL);
	i = 0;
	idx = 0;
	(*lst)->n_sets = mov_amount(lst, 't', space);
	p_sets[idx++] = (*lst)->shape;
	horizontal = mov_amount(lst, 'h', space);
	vertical = mov_amount(lst, 'v', space);
	while (i < vertical)
	{
		while (IS_EXIST(ft_move(p_sets[idx - 1], 'r', space)) == YES)
		{
			p_sets[idx] = ft_move(p_sets[idx - 1], 'r', space);
			idx++;
		}
		p_sets[idx++] = ft_move(p_sets[horizontal * i++], 'd', space);
	}
	p_sets[--idx] = (void *)0;
	return (p_sets);
}

int		mov_amount(t_lst **lst, char way, int space)
{
	int hrz;
	int vtc;
	char *temp;

	hrz = 1;
	vtc = 1;
	temp = (*lst)->shape;
	while(IS_EXIST(ft_move(temp, 'r', space)) == YES)
	{
		temp = ft_move(temp, 'r', space);
		hrz++;
	}
	while(IS_EXIST(ft_move(temp, 'd', space)) == YES)
	{
		temp = ft_move(temp, 'd', space);
		vtc++;
	}
	if (way == 'h')
		return (hrz);
	else if (way == 'v')
		return (vtc);
	else if (way == 't')
		return (hrz * vtc);
	return (0);
}