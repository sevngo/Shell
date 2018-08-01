#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Copies the string `src`, from index `start`, to `dst`.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strrcpy(char *dst, const char *src, size_t start)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(src + i) && i < start)
		i++;
	while (*(src + i))
		*(dst + j++) = *(src + i++);
	*(dst + j) = '\0';
	return (dst);
}
