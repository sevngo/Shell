#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Outputs each string of the array `arr` to the standard output.
**	-------------------------------------------------------------------------- +
*/

void	ft_putarr(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
	{
		ft_putendl(*(arr + i));
		i++;
	}
}
