#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memccpy
**	-------------------------------------------------------------------------- +
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	ptr = dst;
	while (n > ++i)
	{
		*(ptr + i) = *((unsigned char *)src + i);
		if (*(ptr + i) == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
