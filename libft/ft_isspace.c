/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 14:59:35 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 14:59:35 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	unsigned char sym;

	sym = (unsigned char)c;
	if (sym == '\n' || sym == '\t' || sym == '\v' || sym == '\r'
	|| sym == '\f' || sym == ' ')
		return (1);
	return (0);
}
