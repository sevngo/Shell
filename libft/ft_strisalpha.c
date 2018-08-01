#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Tells if a string is composed of alpha characters only.
**	-------------------------------------------------------------------------- +
*/

int	ft_strisalpha(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		if (!ft_isalpha(*(str + i++)))
			return (0);
	return (1);
}
