#include "fillit.h"

char	*ft_move(char *t, char direction, int space)
{
	char	*temp;

	if(!t)
		return (NULL);
	temp = NULL;
	if (direction == 'u')
		temp = bw_shift_left(t, space) ;
	else if (direction == 'd')
		temp = bw_shift_right(t, space);
	else if (direction == 'r')
		temp = bw_shift_right(t, 1);
	else if (direction == 'l')
		temp = bw_shift_left(t, 1);
	if (is_same_shape(t, temp, space) == YES)
		return (temp);
	ft_strdel(&temp); // it has invalid form free!
	return (NULL);
}

void		put_top_left(char **shape, int space)
{
	char *temp;

	while ((temp = ft_move(*shape, 'u', space)))
	{
		ft_strdel(shape);
		*shape = ft_strdup(temp);
		ft_strdel(&temp);
	}
	while ((temp = ft_move(*shape, 'l', space)))
	{
		ft_strdel(shape);
		*shape = ft_strdup(temp);
		ft_strdel(&temp);
	}
}

int		is_same_shape(char *shape, char *moved, int space)
{
	char *temp;
	char *temp2;


	temp = get_shape_hori(shape, space);
	temp2 = get_shape_hori(moved, space);
	if (ft_strcmp(temp, temp2) != 0)
	{
		ft_strdel(&temp);
		ft_strdel(&temp2);
		return (NO);
	}
	ft_strdel(&temp);
	ft_strdel(&temp2);
	temp = get_shape_vert(shape, space);
	temp2 = get_shape_vert(moved, space);
	if (ft_strcmp(temp, temp2) != 0 )
	{
		ft_strdel(&temp);
		ft_strdel(&temp2);
		return (NO);
	}
	ft_strdel(&temp);
	ft_strdel(&temp2);
	return (YES);
}

void	adjust_shape_by_space(t_lst **t, int space, int tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	
	if ((int)ft_strlen((*t)->shape) == ft_pow(space, 2))
		return ;
	temp = ft_memalloc(ft_pow(space, 2) + 1);
	while (i < space)
	{
		j = 0;
		while (i < tab && j < tab)
		{
			temp[i * space + j] = (*t)->shape[i * tab + j];
			j++;
		}
		while (i < space && j < space)
			temp[i * space + j++] = '0';
		i++;
	}
	temp[ft_pow(space, 2)] = '\0';
	ft_strdel(&((*t)->shape));
	(*t)->shape = ft_strdup(temp);
	ft_strdel(&temp);
}

void		adjust_shape_for_small(t_lst **t, int *space)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;
	//space should be 3!!!!
	i = -1;
	count = 0;
	tmp = ft_memalloc(ft_pow(3, 2) + 1);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			tmp[j + (i * 3)] = (*t)->shape[j + (i * 3) + i];
			count += tmp[j + i * 3] == '1';
		}
	}
	if (count != PIECE_SIZE)
		return ;
	*space = 3;
	ft_strdel(&((*t)->shape));
	(*t)->shape = ft_strdup(tmp);
	ft_strdel(&tmp);
}


