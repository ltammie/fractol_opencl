#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *p;

	p = (unsigned char *)s;
	ft_memset(p, '\0', n);
}
