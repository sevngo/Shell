#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Copies an array of string with `size` more element. Sets the first one
**	after the copied tab to NULL, the others are not initialized.
**	-------------------------------------------------------------------------- +
*/

char	**ft_arrndup(char **arr, int size)
{
	char	**ret;
	int		i;
	int		n;

	n = ft_arrlen(arr);
	i = 0;
	if (!(ret = ft_memalloc(sizeof(char *) * (n + size + 1))))
		return (NULL);
	while (i < n && i < (n + size))
	{
		if (!(*(ret + i) = ft_strdup(*(arr + i))))
			return (NULL);
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}
