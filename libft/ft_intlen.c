#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the lenght of an integer (in term of bytes).
**	-------------------------------------------------------------------------- +
*/

size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n = -n;
	while ((n /= 10) != 0)
		i++;
	return (i + 1);
}
