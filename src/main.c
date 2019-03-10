#include "fillit.h"

void	print_answer(t_lst **t, int space, char **ans)
{
	t_lst	*lst;
	char	*res;
	int		i;
	int		width;

	width = ft_pow(space, 2);
	res = ft_memalloc(width + 1);
	lst = (*t);
	ft_strdel(ans);
	while((i = -1) && IS_EXIST(lst) == YES)
	{
		while(++i < width)
			if(lst->p_sets[lst->curr][i] == '1')
				res[i] = lst->idx + 'A';
		lst = lst->next;
	}
	while (++i < width)
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
	if (idx == 1 && two_by_two_one_piece(&head) == 1)
		return (0);
	else 
		make_fillit(&head, idx);
	return (0);
}