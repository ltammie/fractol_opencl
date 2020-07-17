#include "libft.h"

int		ft_isspace(int c)
{
	unsigned char sym;

	sym = (unsigned char)c;
	if (sym == '\n' || sym == '\t' || sym == '\v' || sym == '\r'
	|| sym == '\f' || sym == ' ')
		return (1);
	return (0);
}
