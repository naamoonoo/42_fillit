#include "libft.h"

static char	*make_base(char *base, int str_base)
{
	int		i;
	char	base_set[] = "0123456789abcdef";

	i = -1;
	while (++i < str_base)
		base[i] = base_set[i];
	base[i] = '\0';
	return (base);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		ans;
	int		is_minus;
	char	base[str_base + 1];

	i = ft_start_idx(str);
	is_minus = 0;
	ans = 0;
	make_base(base, str_base);
	if (str[i] == '-' || str[i] == '+')
		is_minus = str[i++] == '-' ? 1 : 0;
	while (str[i])
	{
		if (ft_strchr_idx(base, str[i]) < 0)
			return (0);
		else
			ans = ans * str_base + ft_strchr_idx(base, str[i++]);
	}
	return (is_minus ? ans * -1 : ans);
}