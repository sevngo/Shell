#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 memmove
**	-------------------------------------------------------------------------- +
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	if (dst < src)
		ft_memcpy(dst, src, len);
	return (dst);
}
