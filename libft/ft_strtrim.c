/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:05:25 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:05:25 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	len;
	size_t	start;
	size_t	end;
	char	*new_str;

	i = 0;
	len = 0;
	start = 0;
	if (s)
	{
		end = ft_strlen(s);
		while (ft_isspace(s[start]))
			start++;
		while (end && ft_isspace(s[end - 1]))
			end--;
		len = (end > start) ? (end - start) : 0;
		if ((new_str = ft_strnew(len)))
			while (start < end)
				new_str[i++] = s[start++];
		else
			return (NULL);
		return (new_str);
	}
	return (NULL);
}
