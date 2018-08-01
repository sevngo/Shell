#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Sorts the given array of char-pointers by ASCII value (lowest to highest).
**	-------------------------------------------------------------------------- +
*/

void	ft_arrsort(char **arr)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = ft_arrlen(arr);
	while (i < len)
	{
		j = 0;
		while (j < len && *(arr + j))
		{
			if (*(arr + j + 1) && ft_strcmp(*(arr + j), *(arr + j + 1)) > 0)
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = tmp;
			}
			j++;
		}
		i++;
	}
}
