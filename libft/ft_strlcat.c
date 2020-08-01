/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:04:40 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:04:40 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i != size)
		i++;
	k = i;
	if (i == size)
		return (ft_strlen(src) + i);
	else
	{
		while (src[j] != '\0' && j != size - k)
			dst[i++] = src[j++];
		if (src[j] == '\0' && j != size - k)
			dst[i] = '\0';
		else if (j == size - k)
			dst[i - 1] = '\0';
		return (ft_strlen(src) + k);
	}
}
