/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:42:19 by hnam              #+#    #+#             */
/*   Updated: 2019/02/15 19:42:19 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_by(char const *s, char condition)
{
	int		start;
	int		len;
	char	*res;

	start = 0;
	if (s == NULL)
		return (NULL);
	while (s[start] == condition)
		start++;
	len = ft_strlen(s);
	if (start == len)
		len = 0;
	while (len > 0 && s[len - 1] == condition)
		len--;
	len = len == 0 ? len : len - start;
	if (!(res = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	res = ft_strsub(s, start, len);
	return (res);
}
