#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strncat
**	-------------------------------------------------------------------------- +
*/

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = -1;
	while (*(s2 + ++j) && n > j)
		*(s1 + i++) = *(s2 + j);
	*(s1 + i) = '\0';
	return (s1);
}
