#include "fillit.h"

// typedef struct		s_list
// {
// 	char			*shpae;
// 	int				idx;
// 	int				counter;
// 	struct s_lst	*next;
// 	struct s_lst	*prev;
// }					t_lst;

t_lst	*make_chain_lst(t_lst **head, t_lst **lst, char *buf, int *idx)
{
	t_lst	*t;

	if(!(t = malloc(sizeof(t_lst))))
		return (0);
	t->shape = ft_strdup(buf);
	while(ft_move(t->shape, 'u'))
		t->shape = ft_move(t->shape, 'u');
	while(ft_move(t->shape, 'l'))
		t->shape = ft_move(t->shape, 'l');
	t->p_sets = possilbe_sets(&t);
	t->idx = *idx;
	t->curr = 0;
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
	return (t);
}

int		ft_movable_amount(t_lst **lst, char way)
{
	int hrz;
	int vtc;
	char *temp;

	hrz = 1;
	vtc = 1;
	temp = (*lst)->shape;
	while(ft_move(temp, 'r'))
	{
		temp = ft_move(temp, 'r');
		hrz++;
	}
	while(ft_move(temp, 'd'))
	{
		temp = ft_move(temp, 'd');
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

char 	**possilbe_sets(t_lst **lst)
{
	char	**p_sets;
	int		horizontal;
	int		vertical;
	int		i;
	int		idx;

	if(!(p_sets = (char **)malloc(sizeof(char *) * (ft_movable_amount(lst, 't') + 1))))
		return (NULL);
	i = 0;
	idx = 0;
	p_sets[idx++] = (*lst)->shape;
	horizontal = ft_movable_amount(lst, 'h');
	vertical = ft_movable_amount(lst, 'v');
	while (i < vertical)
	{
		while (ft_move(p_sets[idx - 1], 'r'))
		{
			p_sets[idx] = ft_move(p_sets[idx - 1], 'r');
			idx++;
		}
		p_sets[idx++] = ft_move(p_sets[horizontal * i++], 'd');
	}
	p_sets[--idx] = (void *)0;
	return (p_sets);
}
