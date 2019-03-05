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

int		is_same_shape(char *shape, char *moved)
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
	t_s = get_shape(shape);
	t_m = get_shape(moved);
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

char		*get_shape(char *buf)
{
	int i;
	int j;
	int temp;
	char *res;

	i = 0;
	j = 0;
	temp = 0;
	res = (char *)malloc(sizeof(char) * 5);
	while (i < 16)
	{
		temp += buf[i++] == '1' ? 1 : 0;
		if (i % 4 == 0 && temp != 0)
		{
			res[j++] = temp + '0';
			temp = 0;
		}
	}
	res[j] = '\0';
	return (res);
}

char	*ft_move(char *t, char direction)
{
	int 	n_tmp;
	char	*temp;

	if(!t)
		return (NULL);
	n_tmp = ft_atoi_base(t, 2);
	if (direction == 'u')
		n_tmp = n_tmp << 4;
	else if (direction == 'd')
		n_tmp = n_tmp >> 4;
	else if (direction == 'r')
		n_tmp = n_tmp >> 1;
	else if (direction == 'l')
		n_tmp = n_tmp << 1;
	temp = ft_itoa_base(n_tmp, 2, 16);
	if (is_same_shape(t, temp))
		return (temp);
	//need to free
	ft_strdel(&temp); // it has invalid form free!
	return (NULL);
}

void	pretty_printer(char *shape)
{
	int idx;

	idx = -1;
	if (!shape)
		return ft_putstr("---------Invalid form-----------\n");
	ft_putchar('\n');

	while(++idx < 4)
	{
		ft_putstr(ft_strsub(shape, idx * 4 , 4));
		ft_putchar('\n');
	}
}

void	testing_tool(char *shape, char dir)
{
	char *d;

	d = NULL;
	if (dir == 'u')
		d = ft_strdup("UP");
	else if (dir == 'd')
		d = ft_strdup("DOWN");
	else if (dir == 'r')
		d = ft_strdup("RIGHT");
	else if (dir == 'l')
		d = ft_strdup("LEFT");

	printf("%s\n", d);
	pretty_printer(ft_move(shape, dir));
	printf("%s %s\n", d, d);
	pretty_printer(ft_move(ft_move(shape, dir), dir));
	printf("%s %s %s\n", d, d, d);
	pretty_printer(ft_move(ft_move(ft_move(shape, dir), dir), dir));
}