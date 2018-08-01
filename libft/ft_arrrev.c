#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Reverses the order of the string in the given array.
**	-------------------------------------------------------------------------- +
*/

void	ft_arrrev(char **arr)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_arrlen(arr) - 1;
	while (i <= j)
	{
		tmp = *(arr + i);
		*(arr + i) = *(arr + j);
		*(arr + j) = tmp;
		i++;
		j--;
	}
}
