#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Computes the lenght of the given array.
**	-------------------------------------------------------------------------- +
*/

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = -1;
	if (arr == NULL)
		return (0);
	while (*(arr + ++i))
		;
	return (i);
}
