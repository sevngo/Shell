#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Duplicates the string `s1`, from index `start`.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strrdup(const char *s1, size_t start)
{
	char	*ptr;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) - (start + 1);
	if (!(ptr = ft_strnew(len)))
		return (NULL);
	ft_strrcpy(ptr, s1, start);
	return (ptr);
}
