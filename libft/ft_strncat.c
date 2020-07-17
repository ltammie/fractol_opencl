#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len1;
	size_t len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (i < n)
	{
		if (i < len2)
		{
			s1[len1] = s2[i];
		}
		else
			break ;
		len1++;
		i++;
	}
	s1[len1] = '\0';
	return (s1);
}
