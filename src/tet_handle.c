#include "fillit.h"

int		converter_to_bin(char *buf, int *counter)
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
	if (i != 16 || is_error_exist(buf))
		return (1);
	return (0);
}

char	*ft_move(char *t, char direction, int space)
{
	int		width;
	char	*temp;

	if(!t)
		return (NULL);
	temp = NULL;
	width = ft_pow(space, 2);
	if (direction == 'u')
		temp = bw_shift_left(t, space);
	else if (direction == 'd')
		temp = bw_shift_right(t, space);
	else if (direction == 'r')
		temp =bw_shift_right(t, 1);
	else if (direction == 'l')
		temp = bw_shift_left(t, 1);
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
	*ans = bw_xor(*ans, (*t)->prev->p_sets[(*t)->prev->curr]);
	return (*ans);
}