#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (fd == -1)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
}
