// char	*fillit_btracking(char **ans, t_lst **t)
// {
// 	if(is_valid_set(ans, t))
// 		if((*t)->next)
// 			return fillit_btracking(ans, &((*t)->next));
// 	if(!is_valid_set(ans, t))
// 	{
// 		if ((*t)->curr + 1 != (*t)->n_sets)
// 		{
// 			(*t)->curr += 1;
// 			// printf("일단 움직여 볼 수 있을때\n");
// 			return fillit_btracking(ans, t);
// 		}
// 		else
// 		{
// 			// printf("더이상못움직여서 그 전으로 가야할때\n");
// 			(*t)->curr = 0;
// 			detaching_self(ans, t);
// 			if((*t)->prev->curr + 1 != (*t)->prev->n_sets)
// 			{
// 				// printf("하나더 올릴 수 있음 지금 curr %d\n", (*t)->curr);	
// 				(*t)->prev->curr += 1;
// 				return fillit_btracking(ans, &(*t)->prev);
// 			}
// 			else
// 			{
// 				// printf("안됨/그 전으로 가야됨, 가기전에 바로 전꺼도 curr = 0으로 만들고가라\n");	
// 				(*t)->prev->curr = 0;
// 				// printf("%d == %d?", (*t)->prev->prev->curr + 1, (*t)->prev->prev->n_sets)
// 				if(!(*t)->prev->prev)
// 					return (NULL);
// 				detaching_self(ans, &(*t)->prev);	
// 				(*t)->prev->prev->curr += 1;
// 				return fillit_btracking(ans, &(*t)->prev->prev);
// 			}
// 		}
// 	}
// 	return (*ans);
// }