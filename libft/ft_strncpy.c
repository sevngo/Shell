#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strncpy
**	-------------------------------------------------------------------------- +
*/

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = -1;
	while (*(src + ++i) && i < len)
		*(dst + i) = *(src + i);
	i--;
	while (++i < len)
		*(dst + i) = '\0';
	return (dst);
}
