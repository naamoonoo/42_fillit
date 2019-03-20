/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_not.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkjornra <bkjornra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:27 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 00:42:59 by bkjornra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*bw_not(char *b1)
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	if (!b1)
		return (NULL);
	len = ft_strlen(b1);
	res = ft_memalloc(len + 1);
	while (i < len)
	{
		res[i] = (b1[i] == '1') ? '0' : '1';
		i++;
	}
	return (res);
}
