#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Frees each string of the given array, then sets its pointer to NULL.
**	-------------------------------------------------------------------------- +
*/

void	ft_arrfree(char **arr)
{
	size_t	i;

	i = -1;
	if (arr != NULL)
	{
		while (*(arr + ++i))
			ft_free(*(arr + i));
		ft_free(arr);
	}
}
