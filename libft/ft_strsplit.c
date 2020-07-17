#include "libft.h"

static size_t	word_len(char const *s, char c, size_t i)
{
	size_t j;

	j = i;
	while (s[j] && s[j] != c)
		j++;
	return (j - i);
}

static void		*ft_strfree(char **s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		ft_strdel(&s[i++]);
	free(s);
	s = NULL;
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_count_words(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			len = word_len(s, c, i);
			if (!(arr[j++] = ft_strsub(s, i, len)))
				return (ft_strfree(arr, j - 1));
			i = i + len - 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
