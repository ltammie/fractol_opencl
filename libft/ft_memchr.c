#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char symbol;

	str = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (n)
	{
		if (*str == symbol)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
