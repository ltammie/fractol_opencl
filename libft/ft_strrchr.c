/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:43:08 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 20:25:50 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	sym;
	char			*str;
	size_t			len;
	size_t			i;

	sym = (unsigned char)c;
	str = (char *)s;
	len = ft_strlen(s);
	i = 0;
	while (len > i)
	{
		if (str[len] == c)
			return (&str[len]);
		len--;
	}
	if (str[0] == c)
		return (&str[0]);
	return (NULL);
}
