#include "fillit.h"

#include <stdio.h>

// typedef struct		s_list
// {
// 	char			*shpae;
// 	int				idx;
// 	int				counter;
// 	struct s_lst	*next;
// 	struct s_lst	*prev;
// }					t_lst;

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
			converter(buf, &counter);
			lst = make_chain_lst(&head, &lst, buf, &idx);
			ft_memset(buf, 0, 16);
		}
		ft_strdel(&temp);
	}
	fillit(&head);
	return (0);
}
	
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
