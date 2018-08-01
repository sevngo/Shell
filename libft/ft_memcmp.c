#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memcmp
**	-------------------------------------------------------------------------- +
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = -1;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (n > ++i)
		if (*(ptr1 + i) != *(ptr2 + i))
			return (*(ptr1 + i) - *(ptr2 + i));
	return (0);
}
