#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memchr
**	-------------------------------------------------------------------------- +
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	ptr = (unsigned char *)s;
	while (n > ++i)
		if (*(ptr + i) == (unsigned char)c)
			return ((void *)(s + i));
	return (NULL);
}
