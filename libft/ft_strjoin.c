#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*new_str;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new_str = ft_strnew(len1 + len2)))
		return (NULL);
	while (++i < len1)
		new_str[i] = s1[i];
	i = 0;
	while (i < len2)
		new_str[len1++] = s2[i++];
	new_str[len1 + len2 + 1] = '\0';
	return (new_str);
}
