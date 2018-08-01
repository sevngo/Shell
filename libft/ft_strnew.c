#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’.
**	Each character of the string is initialized at ’\0’.
**	If the allocation fails the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
