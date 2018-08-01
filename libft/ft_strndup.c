#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strndup
**	-------------------------------------------------------------------------- +
*/

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;

	if (!(ptr = ft_strnew(n)))
		return (NULL);
	ft_strncpy(ptr, s1, n);
	*(ptr + n) = '\0';
	return (ptr);
}
