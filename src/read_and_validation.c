/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkjornra <bkjornra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:37 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 00:19:03 by bkjornra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		reading_tetrimono(int fd, t_lst **lst, int *idx)
{
	char	buf[17] = { 0 };
	char	*temp;
	int		count;
	
	count = 0;
	while (get_next_line(fd, &temp) > 0)
	{
		ft_strcat(buf, temp);
		count++;
		if (ft_strlen(buf) > 16 || ft_strlen(temp) > 4
			|| ft_strlen(buf) % 4 != 0)
			return (ERROR);
		else if (ft_strlen(buf) == 16 && count == 5)
		{
			if (converter(buf, &count) == ERROR)
				return (ERROR);
			make_chain_lst(lst, buf, idx);
		}
		ft_strdel(&temp);
	}
	if (ft_strlen(buf) == 16 && count == 4 && (converter(buf, &count) != ERROR))
		make_chain_lst(lst, buf, idx);
	else
		return (ERROR);
	return (SUCCESS);
}

int		converter(char *buf, int *count)
{
	int i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '#')
			buf[i] = '1';
		else if (buf[i] == '.')
			buf[i] = '0';
		else
			return (ERROR);
	}
	*count = 0;
	if (i != 16 || is_valid_shape(buf) == ERROR)
		return (ERROR);
	return (0);
}

int		is_valid_shape(char *shape)
{
	int i;
	int count;
	int sum_of_hor_vert;
	char *temp;

	i = 0;
	count = 0;
	temp = get_shape_hori(shape, PIECE_SIZE);
	while (temp[i])
		count += temp[i++] - '0';
	if (IS_EXIST(ft_strchr(temp, '0')) == YES || count != PIECE_SIZE)
		return (ERROR);
	sum_of_hor_vert = ft_strlen(temp);
	ft_strdel(&temp);
	i = 0;
	count = 0;
	temp = get_shape_vert(shape, PIECE_SIZE);
	while (temp[i])
		count += temp[i++] - '0';
	if (IS_EXIST(ft_strchr(temp, '0')) == YES || count != PIECE_SIZE)
		return (ERROR);
	sum_of_hor_vert += ft_strlen(temp);
	ft_strdel(&temp);
	return ((sum_of_hor_vert != 4 && sum_of_hor_vert != 5) ? ERROR : 0);
}

char	*get_shape_vert(char *shape, int space)
{
	int i;
	int j;
	int temp;
	int width;
	char *tmp;
	char *res;

	i = 0;
	j = 0;
	temp = 0;
	width = ft_pow(space, 2);
	tmp = ft_memalloc(space + 1);
	while (i < width)
	{
		temp += shape[i++] == '1' ? 1 : 0;
		if (i % space == 0)
		{
			tmp[j++] = temp + '0';
			temp = 0;
		}
	}
	tmp[j] = '\0';
	res = ft_strtrim_by(tmp, '0');
	ft_strdel(&tmp);
	return (res);
}

char	*get_shape_hori(char *shape, int space)
{
	int i;
	int j;
	char *temp;
	char *res;

	i = -1;
	temp = ft_memalloc(space + 1);
	ft_memset(temp, '0', space);
	while (++i < space)
	{
		j = -1;
		while (++j < space)
			temp[i] += shape[i + j * space] == '1' ? 1 : 0;
	}
	res = ft_strtrim_by(temp, '0');
	ft_strdel(&temp);
	return (res);
}
