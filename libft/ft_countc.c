#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the number of occurences of the given character in the given string.
**	-------------------------------------------------------------------------- +
*/

int	ft_countc(char *str, char c)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			counter++;
		i++;
	}
	return (counter);
}
