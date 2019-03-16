#include "fillit.h"

void	print_answer(t_lst **t, int space, char **ans)
{
	char	*res;
	char	*temp;
	int		i;
	int		width;

	width = ft_pow(space, 2);
	res = ft_memalloc(width + 1);
	ft_strdel(ans);
	while ((*t)->prev)
		(*t) = (*t)->prev;
	while((i = -1) && IS_EXIST((*t)) == YES)
	{
		while(++i < width)
			if((*t)->p_sets[(*t)->curr][i] == '1')
				res[i] = (*t)->idx + 'A';
		(*t) = (*t)->next;
	}
	while (++i < width)
		if(IS_EXIST(res[i]) == NO)
			res[i] = '.';
	i = -1;
	while(++i < space)
	{
		temp = ft_strsub(res, i * space , space);
		ft_putendl(temp);
		ft_strdel(&temp);
	}
	ft_strdel(&res);
}

int		print_error(void)
{
	ft_putstr("error\n");
	return (1);
}

int		two_by_two_one_piece(t_lst **head)
{
	int		ret;
	char	*t_hori;
	char	*t_vert;

	ret = 0;
	t_hori = get_shape_hori((*head)->shape, PIECE_SIZE);
	t_vert = get_shape_vert((*head)->shape, PIECE_SIZE);
	if ((ft_strcmp("22", t_hori) == 0) && (ft_strcmp("22", t_vert) == 0))
	{
		ft_putendl(MIN_SQUARE);
		ret = 1;
	}
	ft_strdel(&t_hori);
	ft_strdel(&t_vert);
	return (ret);
}

void	freeing_whole_lst(t_lst **lst)
{
	int		i;

	while ((*lst))
	{
		free((*lst)->shape);
		i = 0;
		while((*lst)->p_sets[i])
			free((*lst)->p_sets[i++]);
		free((*lst)->p_sets);
		free((*lst));
		(*lst) = (*lst)->next;
	}
}

int main(int argc, char *argv[])
{
	int		fd;
	int		idx;
	t_lst	*lst;

	idx = 0;
	if (argc != 2)
	{
		ft_putstr("./fillit filename\n");
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error());
	if (reading_tetrimono(fd, &lst, &idx) == ERROR)
		return (print_error());
	while(lst->prev)
		lst = lst->prev;
	if (idx == 1 && two_by_two_one_piece(&lst))
		return (0);
	make_fillit(&lst, idx);


	// while (lst)
	// {
	// 	free(lst->shape);
	// 	// printf("%s will be freed\n", lst->p_sets[lst->n_sets - 1]);
	// 	int i = 0;
	// 	while(lst->p_sets[i])
	// 	{
	// 		printf("%s is freed\n", lst->p_sets[i++]);
	// 		// free(lst->p_sets[lst->n_sets - 1]);
			
	// 	}
	// 	free(lst->p_sets);
	// 	free(lst);
	// 	lst = lst->next;
	// }


	freeing_whole_lst(&lst);
	while(1)
		sleep(1);
	
	return (0);
}