#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char *p;
	unsigned char a;

	p = (unsigned char *)s;
	a = (unsigned char)c;
	while (len--)
	{
		*p = a;
		p++;
	}
	return (s);
}
