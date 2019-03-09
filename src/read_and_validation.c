#include "fillit.h"

int		reading_tetrimono(int fd, t_lst **head, int *idx)
{
	char	buf[17] = { 0 };
	char	*temp;
	t_lst	*lst;
	int		count;
	
	count = 0;
	while (get_next_line(fd, &temp) > 0)
	{
		count++;
		ft_strcat(buf, temp);
		if(ft_strlen(temp) > 4 || ft_strlen(buf) % 4 != 0)
			return (ERROR);
		else if (ft_strlen(buf) == 16 && count == 5)
		{
			if(converter(buf, &count) == ERROR)
				return (ERROR);
			lst = make_chain_lst(head, &lst, buf, idx);
		}
		ft_strdel(&temp);
	}
	if (ft_strlen(buf) == 16 && count == 4 && converter(buf, &count) != ERROR)
		lst = make_chain_lst(head, &lst, buf, idx);
	else
		return (ERROR);
	return (SUCCESS);
    // 이거 else없어도 되는거아님?? ㅅㅂ
}

int		converter(char *buf, int *count)
{
	int i;
	int one_counter;
	int zero_counter;

	i = -1;
	one_counter = 0;
	zero_counter = 0;
	while (buf[++i])
	{
		if (buf[i] == '#')
		{
			buf[i] = '1';
			one_counter++;
		}
		else if (buf[i] == '.')
		{
			buf[i] = '0';
			zero_counter++;
		}
	}
	*count = 0;
	if (i == 16 && one_counter == 4 && zero_counter == 12 
        && is_valid_shape(buf) != ERROR)
		return (0);
	return (ERROR);
}

int		is_valid_shape(char *shape)
{
	int hor;
	int vert;
	char *temp;

	temp = get_shape_vert(shape, PIECE_SIZE);
	if (ft_strchr(temp, '0'))
		return (ERROR);
	vert = ft_strlen(temp);
	ft_strdel(&temp);
	temp = get_shape_hori(shape, PIECE_SIZE);
	if (ft_strchr(temp, '0'))
		return (ERROR);
	hor = ft_strlen(temp);
	ft_strdel(&temp);
	if (hor + vert != 4 && hor + vert != 5)
		return (ERROR);
	return (0);
}


char	*get_shape_vert(char *shape, int space)
{
	int i;
	int j;
	int temp;
	int width;
	char *res;

	i = 0;
	j = 0;
	temp = 0;
	width = ft_pow(space, 2);
	res = ft_memalloc(space + 1);
	// ft_memset(res, '0', space); 이거로 바꿀순 없을까?
	while (i < width)
	{
		temp += shape[i++] == '1' ? 1 : 0;
		if (i % space == 0)
		{
			res[j++] = temp + '0';
			temp = 0;
		}
	}
	res[j] = '\0';
	res = ft_strtrim_by(res, '0');
	return (res);
	//need to free
}

char	*get_shape_hori(char *shape, int space)
{
	int i;
	int j;
	char *temp;

	i = -1;
	temp = ft_memalloc(space + 1);
	ft_memset(temp, '0', space);
	while(++i < space)
	{
		j = -1;
		while (++j < space)
			temp[i] += shape[i + j * space] == '1' ? 1 : 0;
	}
	temp = ft_strtrim_by(temp, '0');
	return (temp);
	//need to free
}