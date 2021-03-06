/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkjornra <bkjornra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:41 by hnam              #+#    #+#             */
/*   Updated: 2019/03/20 00:44:41 by bkjornra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*bw_or(char *b1, char *b2)
{
	size_t	i;
	size_t	len;
	char	*res;

	if (!b1 || !b2)
		return (NULL);
	i = 0;
	if ((len = ft_strlen(b1)) != ft_strlen(b2))
		return (NULL);
	res = ft_memalloc(len + 1);
	while (i < len)
	{
		res[i] = (b1[i] == '1' || b2[i] == '1') ? '1' : '0';
		i++;
	}
	return (res);
}
