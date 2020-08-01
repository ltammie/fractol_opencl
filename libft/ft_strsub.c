/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:05:23 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:05:23 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s)
	{
		i = 0;
		if ((sub = ft_strnew(len)))
		{
			while (i < len)
			{
				sub[i] = s[start];
				i++;
				start++;
			}
		}
		else
			return (NULL);
		return (sub);
	}
	else
		return (NULL);
}
