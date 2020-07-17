#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (src[i] != '\0')
			dst[i] = src[i];
		else
			break ;
		i++;
	}
	if (ft_strlen(src) < len)
		while (i < len)
		{
			dst[i] = '\0';
			i++;
		}
	return (dst);
}
