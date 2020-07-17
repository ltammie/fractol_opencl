#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	sym;
	char			*str;
	size_t			len;
	size_t			i;

	sym = (unsigned char)c;
	str = (char *)s;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (*str == c)
			return (str);
		str++;
		i++;
	}
	return (NULL);
}
