#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’,
**	result of the concatenation of `s1` and `s2`.
**	If the allocation fails the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2 || !(ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	return (ptr);
}
