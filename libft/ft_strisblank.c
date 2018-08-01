#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Iterates over the given string, and checks if it is composed of blank
**	(as defined in ft_isspace()) characters only.
**	-------------------------------------------------------------------------- +
*/

int	ft_strisblank(char *str)
{
	size_t	counter;
	int		i;

	i = 0;
	counter = 0;
	if (!str || ft_strlen(str) == 0)
		return (1);
	while (*(str + i))
		if (ft_isspace(*(str + i++)) == 1)
			counter++;
	return (counter == ft_strlen(str) ? 1 : 0);
}
