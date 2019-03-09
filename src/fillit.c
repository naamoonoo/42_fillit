#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	int		width;
	char	*ans;
	t_lst	*head;
	int 	i;

	i = 0;
	head = (*t);
	space = shape_and_sets(&head, space < 2 ? space + 1 : space);
	width = ft_pow(space, 2);
	ans = ft_memalloc(width + 1);
	while(i < width)
		ans[i++] = '0';
	if(IS_EXIST(fillit_btracking(&ans, &head)) == YES)
		return print_answer(&head, space);
	else
	{
		while(IS_EXIST(head))
		{
			head->shape = head->p_sets[0];
			head->curr = 0;
			head = head->next;
		}
		ft_strdel(&ans);
		return make_fillit(t, space + 1);
	}
}

char	*fillit_btracking(char **ans, t_lst **t)
{
	if(is_valid_set(ans, t))
		if(IS_EXIST((*t)->next) == YES)
			return fillit_btracking(ans, &((*t)->next));
	if(!is_valid_set(ans, t))
	{
		if (IS_EXIST((*t)->curr + 1 != (*t)->n_sets) == YES)
		{
			(*t)->curr += 1;
			return fillit_btracking(ans, t);
		}
		else
			return go_to_prev(ans, t);
	}
	return (*ans);
}

char	*go_to_prev(char **ans, t_lst **t)
{
	(*t)->curr = 0;
	detaching_self(ans, t);
	if(IS_EXIST((*t)->prev->curr + 1 != (*t)->prev->n_sets) == YES)
	{
		(*t)->prev->curr += 1;
		return fillit_btracking(ans, &(*t)->prev);
	}
	else
	{
		(*t)->prev->curr = 0;
		if(IS_EXIST((*t)->prev->prev) == NO)
			return (NULL);
		detaching_self(ans, &(*t)->prev);	
		(*t)->prev->prev->curr += 1;
		return fillit_btracking(ans, &(*t)->prev->prev);
	}
}

int		is_valid_set(char **ans, t_lst **t)
{
	char	*res;
	int		len;
	int		i;
	int		counter;
	char	*temp;

	i = 0;
	counter = 0;
	temp = (*t)->p_sets[(*t)->curr];
	len = ft_strlen(temp);
	res = bw_or(*ans, temp);
	while (IS_EXIST(res[i]) == YES)
		counter += res[i++] == '1' ? 1 : 0;
	if (counter == (((*t)->idx + 1) * 4))
	{
		*ans = res;
		return (1);
	}
	return (0);
}

char	*detaching_self(char **ans, t_lst **t)
{
	*ans = bw_xor(*ans, (*t)->prev->p_sets[(*t)->prev->curr]);
	return (*ans);
}

// 

void	pretty_printer(char *shape, int space)
{
	int idx;

	idx = -1;
	if (!shape)
		return ft_putstr("---------Invalid form-----------\n");
	ft_putchar('\n');
	while(++idx < space)
	{
		ft_putstr(ft_strsub(shape, idx * space , space));
		ft_putchar('\n');
	}
}