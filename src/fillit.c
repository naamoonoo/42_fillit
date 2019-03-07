#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	int		width;
	char	*ans;
	t_lst	*head;
	int 	i;

	i = 0;
	head = (*t);
	width = ft_pow(space, 2);
	shape_and_sets(&head, space);
	ans = ft_memalloc(width + 1);
	while(i < width)
		ans[i++] = '0';
	if(fillit_btracking(&ans, &head))
		return return_answer(&head, space);
	else
	{
		while(head)
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
	if(is_valid(ans, t))
		if((*t)->next)
			return fillit_btracking(ans, &((*t)->next));
	if(!is_valid(ans, t))
	{
		if ((*t)->curr + 1 != (*t)->n_sets)
		{
			(*t)->curr += 1;
			// printf("일단 움직여 볼 수 있을때\n");
			return fillit_btracking(ans, t);
		}
		else
		{
			// printf("더이상못움직여서 그 전으로 가야할때\n");
			(*t)->curr = 0;
			detaching_self(ans, t);
			if((*t)->prev->curr + 1 != (*t)->prev->n_sets)
			{
				// printf("하나더 올릴 수 있음 지금 curr %d\n", (*t)->curr);	
				(*t)->prev->curr += 1;
				return fillit_btracking(ans, &(*t)->prev);
			}
			else
			{
				// printf("안됨/그 전으로 가야됨, 가기전에 바로 전꺼도 curr = 0으로 만들고가라\n");	
				(*t)->prev->curr = 0;
				// printf("%d == %d?", (*t)->prev->prev->curr + 1, (*t)->prev->prev->n_sets)
				if(!(*t)->prev->prev)
					return (NULL);
				detaching_self(ans, &(*t)->prev);	
				(*t)->prev->prev->curr += 1;
				return fillit_btracking(ans, &(*t)->prev->prev);
			}
		}
	}
	return (*ans);
}





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


void	return_answer(t_lst **t, int space)
{
	//space 필요없음
	t_lst	*lst;
	char	*res;
	int		i;
	int		width;

	width = ft_pow(space, 2);
	res = ft_memalloc(width + 1);
	lst = (*t);
	while((i = -1) && lst)
	{
		while(++i < width)
			if(lst->p_sets[lst->curr][i] == '1')
				res[i] = lst->idx + 'A';
		lst = lst->next;
	}
	while(++i < width)
		if(!res[i])
			res[i] = '.';
	i = -1;
	while(++i < space)
	{
		ft_putstr(ft_strsub(res, i * space , space));
		ft_putchar('\n');
	}
	ft_strdel(&res);
}
