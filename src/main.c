#include "fillit.h"

int main(int argc, char *argv[])
{
	int		fd;
	int		counter;
	int		idx;
	char	*temp;
	char	buf[17]; // not fixed number;
	t_lst	*head;
	t_lst	*lst;

	idx = 0;
	if (argc < 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &temp) > 0)
	{
		counter += ft_strcmp(temp, "\0") != 0 ? 4 : 0;
		ft_strcat(buf, temp);
		if (counter == 16)
		{
			if(converter_to_bin(buf, &counter))
				return (0); 
			lst = make_chain_lst(&head, &lst, buf, &idx);
		}
		ft_strdel(&temp);
	}
	make_fillit(&head, idx);//last idx will come
	return (0);
}
	
	// pretty_printer(head->shape, 4);
	// adjust_shape_by_space(&head, 7);
	// adjust_shape_by_space(&head->next, 8);
	// adjust_shape_by_space(&head->next->next, 9);
	// adjust_shape_by_space(&head->next->next->next, 10);


	// printf("%d number of tertis\n", idx);

	// while(*(lst->p_sets))
	// 	pretty_printer(*(lst->p_sets++));
	// printf("\n");


	// while(head)
	// {
	// 	printf("[head : %d]\n", head->idx);
	// 	pretty_printer(head->shape);
	// 	if(head->next)
	// 		head = head->next;
	// 	else
	// 		break;
	// }
	// while(head->prev)
	// {
	// 	printf("[head : %d]\n", head->prev->idx);
	// 	pretty_printer(head->prev->shape);
	// 	head = head->prev;
	// }
