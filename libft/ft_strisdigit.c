#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Tells if a string is composed of digits only.
**	-------------------------------------------------------------------------- +
*/

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		if (!ft_isdigit(*(str + i++)))
			return (0);
	return (1);
}
