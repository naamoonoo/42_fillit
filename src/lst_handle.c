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
	ft_memset(buf, 0, 16);
	(*lst) = t;
}

int		  shape_and_sets(t_lst **head, int idx)
{
	static int	was_3 = 0;
	t_lst 		*t;
	int			space;
	
	space = 4;
	while (4 * idx > ft_pow(space, 2))
		space++;
	t = (*head);
	was_3 += idx == 2 ? 1 : 0;
	while (IS_EXIST(t) == YES)
	{
		idx == 2 && was_3 == 1 ? adjust_shape_for_small(&t, &space) : 
			adjust_shape_by_space(&t, space, was_3 == 1 ? 3 : PIECE_SIZE);
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
	while (IS_EXIST(ft_move(temp, 'r', space)) == YES)
	{
		temp = ft_move(temp, 'r', space);
		hrz++;
	}
	while (IS_EXIST(ft_move(temp, 'd', space)) == YES)
	{
		temp = ft_move(temp, 'd', space);
		vtc++;
	}
	ft_strdel(&temp);
	if (way == 'h')
		return (hrz);
	else if (way == 'v')
		return (vtc);
	else if (way == 't')
		return (hrz * vtc);
	return (0);
}