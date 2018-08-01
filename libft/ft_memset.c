#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memset
**	-------------------------------------------------------------------------- +
*/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		len--;
	}
	return (b);
}
