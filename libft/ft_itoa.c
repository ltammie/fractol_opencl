/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:26:21 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 20:25:50 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nbr_length(long int n)
{
	int size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	long long int	tmp_n;
	int				len;
	char			*nbr;

	tmp_n = (long long int)n;
	len = nbr_length(tmp_n);
	if (!(nbr = ft_strnew(len)))
		return (NULL);
	if (tmp_n < 0)
		tmp_n = tmp_n * -1;
	while (len)
	{
		nbr[--len] = tmp_n % 10 + '0';
		tmp_n = tmp_n / 10;
	}
	if (n < 0)
		nbr[0] = '-';
	return (nbr);
}
