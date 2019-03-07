#include "fillit.h"

void	make_fillit(t_lst **t, int space)
{
	char *ans;
	t_lst *head;

	head = (*t);
	shape_and_sets(t, space);
	ans = detaching_self(&head->shape, &head->next);

	fillit_btracking(&ans, &head);
	printf("정답이면!!\n");
	pretty_printer(head->shape, space);
	
	// printf("ans %d!!\n", is_valid(&ans, &head, space));
	printf("아니면!!\n");
	pretty_printer((*t)->p_sets[0], space);

	if (is_valid(&ans, &head, space))
		pretty_printer(ans, space);
	else
	{
		(*t)->shape = (*t)->p_sets[0];
		while((*t))
		{
			(*t)->curr = 0;
			(*t) = (*t)->next;
		}
		return make_fillit(t, space + 1);
	}
}



char	*fillit_btracking(char **ans, t_lst **t)
{
	if(is_valid(ans, t, 0))
		if((*t)->next)
			return fillit_btracking(ans, &((*t)->next));
	if(!is_valid(ans, t, 0))
	{
		if ((*t)->p_sets[(*t)->curr + 1])
		{
			(*t)->curr += 1;
			printf("일단 움직여 볼 수 있을때\n");
			return fillit_btracking(ans, t);
		}
		else
		{
			printf("더이상못움직여서 그 전으로 가야할때\n");
			(*t)->curr = 0;
			detaching_self(ans, t);
			if((*t)->prev->p_sets[(*t)->prev->curr + 1])
			{
				printf("하나더 올릴 수 있음 지금 curr %d\n", (*t)->curr);	
				(*t)->prev->curr += 1;
				return fillit_btracking(ans, &(*t)->prev);
			}
			else
			{
				printf("안됨/그 전으로 가야됨, 가기전에 바로 전꺼도 curr = 0으로 만들고가라\n");	
				(*t)->prev->curr = 0;
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
