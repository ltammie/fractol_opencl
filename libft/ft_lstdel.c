/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 14:59:48 by ltammie           #+#    #+#             */
/*   Updated: 2020/08/01 14:59:48 by ltammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *head;

	if (*alst == NULL)
		return ;
	head = *alst;
	while (head)
	{
		tmp = head->next;
		ft_lstdelone(&head, del);
		head = tmp;
	}
	*alst = NULL;
}
