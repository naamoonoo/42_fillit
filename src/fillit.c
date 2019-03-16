#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	char	*ans;
	t_lst	*head;
	int 	len;

	head = (*t);
	space = shape_and_sets(&head, space);
	if (space == 3 && (ft_strlen(head->shape) != ft_strlen(head->next->shape)))
		return (make_fillit(t, PIECE_SIZE));
	len = ft_pow(space, 2);
	ans = ft_memalloc(len + 1);
	while (len-- != 0)
		ans[len] = '0';
	if (IS_EXIST(fillit_btracking(&ans, &head)) == YES)
		return (print_answer(&head, space, &ans));
	else
	{
		while (IS_EXIST(head))
		{	
			free(head->shape);
			head->shape = ft_strdup(head->p_sets[0]);
			while(head->n_sets-- != 0)
				free(head->p_sets[head->n_sets]);
			free(head->p_sets);
			head->curr = 0;
			head = head->next;
		}
		ft_strdel(&ans);
		return (make_fillit(t, space + 1));
	}
}


char	*fillit_btracking(char **ans, t_lst **t)
{
	if (is_valid_set(ans, t) == YES)
	{
		if (IS_EXIST((*t)->next) == YES)
			return (fillit_btracking(ans, &((*t)->next)));
		else
			return (*ans);
	}	
	else
	{
		if ((*t)->curr + 1 != (*t)->n_sets)
		{
			(*t)->curr += 1;
			return (fillit_btracking(ans, t));
		}
		else
			return (go_to_prev(ans, t));
	}
}

char	*go_to_prev(char **ans, t_lst **t)
{
	(*t)->curr = 0;
	detaching_self(ans, t);
	if ((*t)->prev->curr + 1 != (*t)->prev->n_sets)
	{
		(*t)->prev->curr += 1;
		return (fillit_btracking(ans, &(*t)->prev));
	}
	else
	{
		(*t)->prev->curr = 0;
		if (IS_EXIST((*t)->prev->prev) == NO)
			return (NULL);
		detaching_self(ans, &(*t)->prev);	
		(*t)->prev->prev->curr += 1;
		return (fillit_btracking(ans, &(*t)->prev->prev));
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
	return (*ans);
}




//for test.

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


// char	*fillit_btracking(char **ans, t_lst **t)
// {
// 	while((*t))
// 	{
// 		if (is_valid_set(ans, t) == YES)
// 		{
// 			if (IS_EXIST((*t)->next) == YES)
// 			{
// 				(*t) = (*t)->next;
// 				continue ;
// 			}
// 			return (*ans);
// 		}
// 		else
// 		{
// 			if ((*t)->curr + 1 != (*t)->n_sets)
// 			{
// 				(*t)->curr += 1;
// 				continue ;
// 			}
// 			else
// 			{
// 				(*t)->curr = 0;
// 				detaching_self(ans, t);
// 				if ((*t)->prev->curr + 1 != (*t)->prev->n_sets)
// 				{
// 					(*t)->prev->curr += 1;
// 					(*t) = (*t)->prev;
// 					continue ;
// 				}
// 				else
// 				{
// 					(*t)->prev->curr = 0;
// 					if (IS_EXIST((*t)->prev->prev) == NO)
// 						return (NULL);
// 					detaching_self(ans, &(*t)->prev);	
// 					(*t)->prev->prev->curr += 1;
// 					(*t) = (*t)->prev->prev;
// 				}
// 			}
// 		}
// 	}
// 	return (*ans);
// }
	

// char	*go_to_prev(char **ans, t_lst **t)
// {
	
// }
