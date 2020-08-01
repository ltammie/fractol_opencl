/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:00:12 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:00:12 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char symbol;

	str = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (n)
	{
		if (*str == symbol)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
