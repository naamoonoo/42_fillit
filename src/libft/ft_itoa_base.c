/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 00:35:41 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 00:35:45 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>



static char	*make_base_set(char *base, int str_base)
{
	int		i;
	char	base_set[] = "0123456789abcdef";

	i = -1;
	if(!(base = (char *)malloc(sizeof(char) * (str_base + 1))))
		return (NULL);
	while (++i < str_base)
		base[i] = base_set[i];
	base[i] = '\0';
	return (base);
}

char	*ft_itoa_base(int n, int str_base, int len)
{
	char	*res;
	char	*base_set;
	int		i;
	int		dv;

	i = 0;
	len = len == 0 ? ft_number_length(ABS(n), str_base) : len;
	dv = ft_pow(str_base, len - 1);
	base_set = NULL;
	if (!(res = (char *)malloc((n < 0 ? len + 2 : len + 1) * sizeof(char))))
		return (NULL);
	if (n == MAX_INT)
		return (ft_strcpy(res, "-2147483648"));
	if (n < 0)
		ft_itoa_minus_handling(&n, res, &len, &i);
	base_set = make_base_set(base_set, str_base);
	while (len-- > 0)
	{
		res[i++] = base_set[n / dv];
		n -= (n / dv) * dv;
		dv /= str_base;
	}
	res[i] = '\0';
	ft_strdel(&base_set);
	return (res);
}
