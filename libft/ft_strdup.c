/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:00:07 by ltammie           #+#    #+#             */
/*   Updated: 2020/02/24 20:25:50 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	size;
	char	*dup;

	i = 0;
	size = ft_strlen(s1);
	if ((dup = (char *)malloc(sizeof(char) * (size + 1))))
	{
		while (i < size)
		{
			dup[i] = s1[i];
			i++;
		}
	}
	else
		return (NULL);
	dup[size] = '\0';
	return (dup);
}
