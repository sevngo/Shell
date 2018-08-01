#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strlcat
**	-------------------------------------------------------------------------- +
*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*ptr1;
	const char	*ptr2;
	size_t		i;
	size_t		len;

	ptr1 = dst;
	ptr2 = src;
	i = size;
	while (*ptr1 && i-- > 0)
		ptr1++;
	len = ptr1 - dst;
	if ((i = size - len) == 0)
		return (len + ft_strlen(ptr2));
	while (*ptr2)
	{
		if (i > 1)
		{
			*ptr1++ = *ptr2;
			i--;
		}
		ptr2++;
	}
	*ptr1 = '\0';
	return (len + (ptr2 - src));
}
