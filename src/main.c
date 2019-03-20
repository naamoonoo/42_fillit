#include "fillit.h"

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
	if (idx == 1 && ft_strcmp(lst->shape, "1100110000000000"))
	{
		ft_putstr(MIN_SQUARE);
		return (0);
	}
	make_fillit(&lst, idx);
	freeing_whole_lst(&lst);
	// while(1)
	// 	sleep(1);
	return (0);
}