#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	char	*ans;
	t_lst	*head;
	int 	len;
	// static int count = 0;

	head = (*t);
	space = shape_and_sets(&head, space);
	if (space == 3 && (ft_strlen(head->shape) != ft_strlen(head->next->shape)))
		return (make_fillit(t, space));
	len = ft_pow(space, 2);
	ans = ft_memalloc(len + 1);
	while (len-- != 0)
		ans[len] = '0';
	// printf("%d칸으로 시작합!", space);
	if (fillit_btracking(&ans, &head) == YES)
		return (print_answer(&head, space, &ans));
	else
	{
		// if(count++ == 1)
		// 	return ;
		// printf("%d칸으로는 안되지? 한칸 늘리자!", space);
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
		return (make_fillit(t, space));
	}
}

int		fillit_btracking(char **ans, t_lst **t)
{
	while ((*t))
	{
		// (*t)->next->idx = 
		// printf("%d번째는 %d조각부터 시작합니다\n", (*t)->idx,(*t)->curr);
		if ((*t)->idx == 0 && (*t)->curr == (*t)->n_sets)
			return (0);
		if (check_is_valid_set(ans, t) == YES)
		{
			// printf("오 이친구 되는구먼!\n");
			if ((*t)->next)
			{
				// printf("아직 조각남았으니까 다음조각으로 ㄱ ㄱ !\n");
				(*t) = (*t)->next;
			}
			else
			{
					// printf("ㅊㅋㄹㅊㅋㄹ 끝나ㅈㅆ쮸!!\n");
				return (1);
				}
		}
		else
		{
			// printf("이 조각이 들어갈곳이 하나도 없네, 앞의 조각을 한칸 옮겨야겠당\n");
			if ((*t)->prev)
			{
				(*t)->curr = 0;
				detaching_self(ans, t);
				(*t) = (*t)->prev;
			}
			// printf("이제 %d번째 가꼬 놀거임\n", (*t)->idx);
		}
	}
		// printf("ㅋㅋㅋㅋ헤드까지 다시 돌아왔네그려 조졌어 ~~\n");
	return (0);
}

int		check_is_valid_set(char **ans, t_lst **t)
{
	// int i;
	// static int ct = 0;
	
	// if(++ct == 10)
	// 	return (-1);
	// i = (*t)->curr;
	while ((*t)->curr < (*t)->n_sets)
	{
		// printf("%d번째 조각의 %d번째를 시작해보지\n", (*t)->idx, (*t)->curr);
		// pretty_printer(*ans, 6);
		// pretty_printer((*t)->p_sets[(*t)->curr], 6);
		if (!(*t)->p_sets[(*t)->curr])
		{
			break ;
		}
		if (is_valid_set(ans, t) == YES)
		{
		// printf("키킥 조각이 딱맞는구먼~\n");
			return (1);
			}
		else
		{
			// printf("다음조각넣어봅시당\n");
			(*t)->curr += 1;
			}
	}

	return (0);
	
}


// char	*fillit_btracking(char **ans, t_lst **t)
// {
// 	if (is_valid_set(ans, t) == YES)
// 	{
// 		if (IS_EXIST((*t)->next) == YES)
// 			return (fillit_btracking(ans, &((*t)->next)));
// 		else
// 			return (*ans);
// 	}	
// 	else
// 	{
// 		if ((*t)->curr + 1 != (*t)->n_sets)
// 		{
// 			(*t)->curr += 1;
// 			return (fillit_btracking(ans, t));
// 		}
// 		else
// 			return (go_to_prev(ans, t));
// 	}
// }

// char	*go_to_prev(char **ans, t_lst **t)
// {
// 	(*t)->curr = 0;
// 	detaching_self(ans, t);
// 	if ((*t)->prev->curr + 1 != (*t)->prev->n_sets)
// 	{
// 		(*t)->prev->curr += 1;
// 		return (fillit_btracking(ans, &(*t)->prev));
// 	}
// 	else
// 	{
// 		(*t)->prev->curr = 0;
// 		if (IS_EXIST((*t)->prev->prev) == NO)
// 			return (NULL);
// 		detaching_self(ans, &(*t)->prev);	
// 		(*t)->prev->prev->curr += 1;
// 		return (fillit_btracking(ans, &(*t)->prev->prev));
// 	}
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
	// printf("앤서시트에서 앞에놈꺼 들어내고, 앞에 조각을 다음거에 넣는거부터 시작합시다\n");
	// pretty_printer(*ans, 6);
	// pretty_printer((*t)->prev->p_sets[(*t)->prev->curr], 6);
	*ans = bw_xor(*ans, (*t)->prev->p_sets[(*t)->prev->curr]);
	// printf("덜어내고나면\n");
	// pretty_printer(*ans, 6);
	(*t)->prev->curr += 1;
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
