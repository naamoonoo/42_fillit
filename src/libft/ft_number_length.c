/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:06:56 by hnam              #+#    #+#             */
/*   Updated: 2019/02/21 17:06:57 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number_length(int n, int base)
{
	if (n < base)
		return (1);
	else
		return (ft_number_length(n % base, base) + ft_number_length(n / base, base));
}
