#include "fillit.h"

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
	if (is_same_shape(t, temp, space) == YES)
		return (temp);
	//need to free
	ft_strdel(&temp); // it has invalid form free!
	return (NULL);
}

int		is_same_shape(char *shape, char *moved, int space)
{
	if (ft_strcmp(get_shape_hori(shape, space), 
		get_shape_hori(moved, space)))
		return (NO);
	if (ft_strcmp(get_shape_vert(shape, space),
	 	get_shape_vert(moved, space)))
		return (NO);
	return (YES);
}

void	adjust_shape_by_space(t_lst **t, int space)
{
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
