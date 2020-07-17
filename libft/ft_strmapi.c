#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*new;

	if (s && f)
	{
		len = ft_strlen(s);
		i = 0;
		new = ft_strnew(len);
		if (!new)
			return (NULL);
		while (s[i] != '\0')
		{
			new[i] = (*f)(i, s[i]);
			i++;
		}
		return (new);
	}
	else
		return (NULL);
}
