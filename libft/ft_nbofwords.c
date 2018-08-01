#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Counts & returns the number of words delimited by the characer `c`,
**	in the given string `s`
**	-------------------------------------------------------------------------- +
*/

int	ft_nbofwords(char *s, char c)
{
	int	counter;
	int	sw;
	int	i;

	i = 0;
	sw = 0;
	counter = 0;
	while (*(s + i))
	{
		if (sw == 1 && *(s + i) == c)
			sw = 0;
		if (sw == 0 && *(s + i) != c)
		{
			sw = 1;
			counter++;
		}
		i++;
	}
	return (counter);
}
