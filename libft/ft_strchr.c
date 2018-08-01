#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strchr
**	-------------------------------------------------------------------------- +
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	return (*s == (char)c ? (char *)s : NULL);
}
