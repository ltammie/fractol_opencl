#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			new[i] = (*f)(s[i]);
			i++;
		}
		return (new);
	}
	else
		return (NULL);
}
