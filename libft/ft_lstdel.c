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
