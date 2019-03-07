#include "fillit.h"

int		is_valid(char **ans, t_lst **t, int space)
{
	char	*res;
	int		len;
	int		i;
	int		counter;
	char	*temp;

	i = 0;
	counter = 0;
	if (space == 0)
		temp = (*t)->p_sets[(*t)->curr];
	else //compare to empty one
		temp = (*t)->shape;
	len = ft_strlen(temp);
	res = ft_itoa_base(ft_atoi_base(*ans, 2) | ft_atoi_base(temp, 2), 2, len);
	while (res[i])
		counter += res[i++] == '1' ? 1 : 0;
	if (counter == ((space == 0 ? (*t)->idx + 1 : space) * 4))
	{
		// printf("--------------------------------\n");
		// pretty_printer(res, 4);
		// printf("--------------------------------\n");
		*ans = res;
		return (1);
	}
	return (0);
}


int		is_same_shape(char *shape, char *moved, int space)
{
	int i;
	int counter;
	int limit;
	int ret;
	char *t_s;
	char *t_m;

	ret = 0;
	i = -1;
	counter = 0;
	t_s = get_shape(shape, space);
	t_m = get_shape(moved, space);
	limit = (int)ft_strlen(t_s);
	if (limit != (int)ft_strlen(t_m))
		ret = 0;
	while(++i < limit)
		counter += (t_s[i] - '0') + (t_m[i] - '0');
	if (counter == 8 && !ft_strcmp(t_s, t_m))
		ret = 1;
	ft_strdel(&t_s);
	ft_strdel(&t_m);
	return (ret == 1 ? 1 : 0 );
}

char	*get_shape(char *buf, int space)
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
	res = (char *)malloc(sizeof(char) * 5);
	while (i < width)
	{
		temp += buf[i++] == '1' ? 1 : 0;
		if (i % space == 0 && temp != 0)
		{
			res[j++] = temp + '0';
			temp = 0;
		}
	}
	res[j] = '\0';
	return (res);
}

