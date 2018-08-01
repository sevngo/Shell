#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strrchr
**	-------------------------------------------------------------------------- +
*/

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen((char *)s);
	while (i > 0 && *(s + i) != (char)c)
		i--;
	return (*(s + i) == (char)c ? (char *)s + i : NULL);
}
