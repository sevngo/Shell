#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memcpy
**	-------------------------------------------------------------------------- +
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = -1;
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (n > ++i)
		*(ptr1 + i) = *(ptr2 + i);
	return (dst);
}
