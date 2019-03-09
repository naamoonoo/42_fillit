#include "fillit.h"

void	print_answer(t_lst **t, int space)
{
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
		if(IS_EXIST(res[i]) == NO)
			res[i] = '.';
	i = -1;
	while(++i < space)
		ft_putendl(ft_strsub(res, i * space , space));
	ft_strdel(&res);
}

int		print_error(void)
{
	ft_putstr("error\n");
	return (1);
}

int main(int argc, char *argv[])
{
	int		fd;
	int		idx;
	t_lst	*head;

	idx = 0;
	if (argc != 2)
	{
		ft_putstr("./fillit filename\n");
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error());
	if (reading_tetrimono(fd, &head, &idx) == ERROR)
		return (print_error());
	if (idx > 1)
		make_fillit(&head, idx);//last idx will come
		// idx == 2일때, 즉 인풋이 2개일때!
	else if (idx == 1)
		if ((ft_strcmp("22", get_shape_hori(head->shape, PIECE_SIZE)) == 0) && 
		(ft_strcmp("22", get_shape_vert(head->shape, PIECE_SIZE)) == 0))
			ft_putendl(MIN_SQUARE);
	// else
	// print_error

	return (0);
}