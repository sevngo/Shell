#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Applies the function `f` to each character of the string given as argument
**	to create a “fresh” new string (with malloc(3)) resulting from the
**	successive applications of `f`.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*ptr;

	i = -1;
	if (!s || !(ptr = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (*(s + ++i))
		*(ptr + i) = f(*(s + i));
	*(ptr + i) = '\0';
	return (ptr);
}
