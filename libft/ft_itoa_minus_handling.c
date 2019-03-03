#include "libft.h"

void	ft_itoa_minus_handling(int *n, char *res, int *len, int *i)
{
	*n = ABS(*n);
	res[*i] = '-';
	*i = *i + 1;
	*len = *len + 1;
}