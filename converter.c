#include "fillit.h"

char	*converter( char *buf, int fd, int *counter)
{
	int i;
	static int idx = 0;

	i = 0;
	while (buf[i])
	{
		buf[i] = buf[i] == '#' ? '1' : '0';
		i++;
	}
	buf[i] = '\0';

	printf("%s\n",ft_itoa_base(ft_atoi_base("0110110000000000", 2) | ft_atoi_base("0011000100010000", 2), 2, 16));
	// ft_strcpy(sets[idx], buf);
	// printf("%s buf", buf);
	ft_memset(buf, 0, 16);
	*counter = 0;
	return (buf);
}

