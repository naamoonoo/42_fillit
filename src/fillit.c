#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	char	*ans;
	t_lst	*head;
	int 	len;

	head = (*t);
	space = shape_and_sets(&head, space);
	if (space == 3 && (ft_strlen(head->shape) != ft_strlen(head->next->shape)))
		return (make_fillit(t, space));
	len = ft_pow(space, 2);
	ans = ft_memalloc(len + 1);
	while (len-- != 0)
		ans[len] = '0';
	if (fillit_btracking(&ans, &head) == YES)
	{
		ft_strdel(&ans);
		return (print_answer(&head, space));
	}
	else
	{
		make_default(t, &ans);
		return (make_fillit(t, space));
	}
}

int		fillit_btracking(char **ans, t_lst **t)
{
	while ((*t))
	{
		if ((*t)->idx == 0 && (*t)->curr == (*t)->n_sets)
			return (0);
		if (check_is_valid_set(ans, t) == YES)
		{
			if ((*t)->next)
				(*t) = (*t)->next;
			else
				return (1);
		}
		else
		{
			if ((*t)->prev)
			{
				(*t)->curr = 0;
				detaching_self(ans, t);
				(*t) = (*t)->prev;
			}
		}
	}
	return (0);
}

int		check_is_valid_set(char **ans, t_lst **t)
{
	while ((*t)->curr < (*t)->n_sets)
	{
		if (!(*t)->p_sets[(*t)->curr])
			break ;
		if (is_valid_set(ans, t) == YES)
			return (1);
		else
			(*t)->curr += 1;
	}
	return (0);
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
		ft_strdel(ans);
		*ans = ft_strdup(res);
		ft_strdel(&res);
		return (YES);
	}
	ft_strdel(&res);
	return (NO);
}
 
char	*detaching_self(char **ans, t_lst **t)
{
	*ans = bw_xor(*ans, (*t)->prev->p_sets[(*t)->prev->curr]);
	(*t)->prev->curr += 1;
	return (*ans);
}
