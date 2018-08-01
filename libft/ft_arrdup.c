#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates sufficient memory for a copy of the given array of char-pointers,
**	does the copy, and returns a pointer to it.
**	-------------------------------------------------------------------------- +
*/

char	**ft_arrdup(char **arr)
{
	char	**ret;
	int		i;

	i = 0;
	if (!arr || !(ret = ft_memalloc(sizeof(char *) * (ft_arrlen(arr) + 1))))
		return (NULL);
	while (*(arr + i))
	{
		if (!(*(ret + i) = ft_strdup(*(arr + i))))
			return (NULL);
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}
