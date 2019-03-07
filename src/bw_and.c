#include "fillit.h"

char	*bw_and(char *b1, char *b2)
{
	size_t	i;
	size_t	len;
	char 	*res;
	
	if (!b1 || !b2)
		return (NULL);
	i = 0;
	if ((len = ft_strlen(b1)) != ft_strlen(b2))
		return (NULL);
	res = ft_memalloc(len + 1);
	while (i < len)
	{
		res[i] = (b1[i] == '1' && b2[i] == '1') ? '1' : '0';
		i++;
	}
	return (res);
}