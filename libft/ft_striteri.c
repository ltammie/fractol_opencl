/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:04:31 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 15:04:31 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t i;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
