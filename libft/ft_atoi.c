#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 atoi
**	-------------------------------------------------------------------------- +
*/

int		ft_atoi(const char *str)
{
	int sign;
	int res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while ((*(str + i) == ' ') || (*(str + i) == '\f') ||
			(*(str + i) == '\n') || (*(str + i) == '\r') ||
				(*(str + i) == '\t') || (*(str + i) == '\v'))
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (ft_isdigit(*(str + i)))
		res = (res * 10) + (int)(*(str + i++) - '0');
	return (sign * res);
}
