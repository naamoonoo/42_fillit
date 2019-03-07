#include "fillit.h"

void	converter(char *buf, int *counter)
{
	int i;

	i = -1;
	buf[*counter] = '\0';
	while (buf[++i])
	{
		buf[i] = buf[i] == '.' ? '0' : '1';
	}
	buf[i] = '\0';
	*counter = 0;
}

char	*ft_move(char *t, char direction, int space)
{
	int 	n_tmp;
	int		width;
	char	*temp;

	if(!t)
		return (NULL);
	width = ft_pow(space, 2);
	n_tmp = ft_atoi_base(t, 2);
	if (direction == 'u')
		n_tmp = n_tmp << space;
	else if (direction == 'd')
		n_tmp = n_tmp >> space;
	else if (direction == 'r')
		n_tmp = n_tmp >> 1;
	else if (direction == 'l')
		n_tmp = n_tmp << 1;
	temp = ft_itoa_base(n_tmp, 2, width);// 여기서 16이 고정값임 이거를 4*idx < ft_pow(n, 2); 형태의 값을 넣어야함
	if (is_same_shape(t, temp, space))
		return (temp);
	//need to free
	ft_strdel(&temp); // it has invalid form free!
	return (NULL);
}

void	adjust_shape_by_space(t_lst **t, int space)
{
	// idx에 1씩 더해가면서 사이즈 조정하기
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = ft_memalloc(ft_pow(space, 2) + 1);
	while (i < space)
	{
		j = 0;
		while (j < 4)
		{
			temp[i * space + j] = i < 4 ? (*t)->shape[i * 4 + j] : '0';
			j++;
		}
		while (j >= 4 && j < space)
			temp[i * space + j++] = '0';
		i++;
	}
	temp[ft_pow(space, 2)] = '\0';
	ft_strdel(&((*t)->shape));
	(*t)->shape = ft_strdup(temp);
	ft_strdel(&temp);
}

char	*detaching_self(char **ans, t_lst **t)
{
	char *self;
	int temp;

	self = (*t)->prev->p_sets[(*t)->prev->curr];

	// printf("ans : \n");
	// pretty_printer(*ans);
	// printf("--- : \n");
	// pretty_printer(self);
	temp = ft_atoi_base(*ans, 2) ^ ft_atoi_base(self, 2);
	*ans = ft_itoa_base(temp, 2, ft_strlen(self));
	// printf("now : \n");
	// pretty_printer(*ans);
	return (*ans);
}