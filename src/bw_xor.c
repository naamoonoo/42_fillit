/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:23:12 by hnam              #+#    #+#             */
/*   Updated: 2019/03/19 23:23:13 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*bw_xor(char *b1, char *b2)
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
		res[i] = (b1[i] == b2[i]) ? '0' : '1';
		i++;
	}
	return (res);
}
