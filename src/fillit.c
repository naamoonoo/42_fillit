#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	char	*ans;
	t_lst	*head;
	int 	i;

	i = 0;
	head = (*t);
	space = shape_and_sets(&head, space);
	if (space == 3 && (ft_strlen((*t)->shape) != ft_strlen((*t)->next->shape)))
		return (make_fillit(t, PIECE_SIZE));
	ans = ft_memalloc(ft_pow(space, 2) + 1);
	while (i < ft_pow(space, 2))
		ans[i++] = '0';
	if (IS_EXIST(fillit_btracking(&ans, &head)) == YES)
		return (print_answer(&head, space, &ans));
	else
	{
		while (IS_EXIST(head))
		{	
			// free(head->shape);
			head->shape = head->p_sets[0];
			// i = 0;
			// while(head->p_sets[i])
			// 	free(head->p_sets[i++]);
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
		if (IS_EXIST((*t)->next) == YES)
		{
			// printf("나는 넣었음, 다음꺼 넣으러 갑시다!\n");
			return (fillit_btracking(ans, &((*t)->next)));
		}
	if (is_valid_set(ans, t) == NO)
	{
		if ((*t)->curr + 1 != (*t)->n_sets)
		{
			(*t)->curr += 1;
			// printf("나는 안되고 내 다음애 있으니까 걔 넣어보셈\n");
			return (fillit_btracking(ans, t));
		}
		else
		// {printf("나는 이미글름, 내 앞에 애로 가쟈\n");
				return (go_to_prev(ans, t));
				// }
	}
	return (*ans);
}

char	*go_to_prev(char **ans, t_lst **t)
{
	(*t)->curr = 0;
	detaching_self(ans, t);
	if ((*t)->prev->curr + 1 != (*t)->prev->n_sets)
	{
		(*t)->prev->curr += 1;
		// printf("내 앞에놈 하나더 옮겨볼수있음\n");
		return (fillit_btracking(ans, &(*t)->prev));
	}
	else
	{
		(*t)->prev->curr = 0;
		if (IS_EXIST((*t)->prev->prev) == NO)
		// {printf("내 앞에 앞에놈도 더이상 못옮긴댜\n");
			return (NULL);
			// }
		detaching_self(ans, &(*t)->prev);	
		(*t)->prev->prev->curr += 1;
		// printf("휴 내 앞에 앞에놈 하나 더 ㄱㄴ 고고링\n");
		return (fillit_btracking(ans, &(*t)->prev->prev));
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