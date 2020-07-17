#include "libft.h"

static int		cake(long long res, char c, int sign)
{
	if ((((res * sign) >= 922337203685477580) && ((c - '0') > 7)) ||
			((res * sign >= 1000000000000000000) && c))
		return (-1);
	else if ((((res * sign) <= -922337203685477580) && ((c - '0') > 8)) ||
			((res * sign <= -1000000000000000000) && c))
		return (0);
	return (1);
}

int				ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	size_t		i;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (cake(result, str[i], sign) == -1)
			return (-1);
		else if (cake(result, str[i], sign) == 0)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
