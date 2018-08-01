#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Applies the function `f` to each character of the string passed as argument.
**	Each character is passed by address to `f` to be modified if necessary.
**	-------------------------------------------------------------------------- +
*/

void	ft_striter(char *s, void (*f)(char *))
{
	size_t	i;

	i = -1;
	if (s && f)
		while (*(s + ++i))
			f(s + i);
}
