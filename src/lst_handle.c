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

void	shape_and_sets(t_lst **head, int idx)
{
	t_lst 	*t;
	int		space;
	
	space = 1;
	while (4 * idx > ft_pow(space, 2))
		space++;
	t = (*head);
	while(t)
	{
		adjust_shape_by_space(&t, space);
		// printf("adjusted shape\n");
		// pretty_printer(t->shape, space);
		while(ft_move(t->shape, 'u', space))
			t->shape = ft_move(t->shape, 'u', space);
		while(ft_move(t->shape, 'l', space))
			t->shape = ft_move(t->shape, 'l', space);
		t->p_sets = possilbe_sets(&t, space);
		t = t->next;
	}
}

int		ft_movable_amount(t_lst **lst, char way, int space)
{
	int hrz;
	int vtc;
	char *temp;

	hrz = 1;
	vtc = 1;
	temp = (*lst)->shape;
	while(ft_move(temp, 'r', space))
	{
		temp = ft_move(temp, 'r', space);
		hrz++;
	}
	while(ft_move(temp, 'd', space))
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

char 	**possilbe_sets(t_lst **lst, int space)
{
	char	**p_sets;
	int		horizontal;
	int		vertical;
	int		i;
	int		idx;

	if(!(p_sets = (char **)malloc(sizeof(char *) * (ft_movable_amount(lst, 't', space) + 1))))
		return (NULL);
	i = 0;
	idx = 0;
	(*lst)->n_sets = ft_movable_amount(lst, 't', space);
	p_sets[idx++] = (*lst)->shape;
	horizontal = ft_movable_amount(lst, 'h', space);
	vertical = ft_movable_amount(lst, 'v', space);
	while (i < vertical)
	{
		while (ft_move(p_sets[idx - 1], 'r', space))
		{
			p_sets[idx] = ft_move(p_sets[idx - 1], 'r', space);
			idx++;
		}
		p_sets[idx++] = ft_move(p_sets[horizontal * i++], 'd', space);
	}
	// printf("last pices is\n");
	// pretty_printer(p_sets[idx - 2], space);
	p_sets[--idx] = (void *)0;
	return (p_sets);
}
