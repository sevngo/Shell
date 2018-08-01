#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strdup
**	-------------------------------------------------------------------------- +
*/

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	if (!(ptr = ft_strnew(ft_strlen(s1))))
		return (NULL);
	return (ft_strcpy(ptr, s1));
}
