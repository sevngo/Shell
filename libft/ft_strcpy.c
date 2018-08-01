#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strcpy
**	-------------------------------------------------------------------------- +
*/

char	*ft_strcpy(char *dst, const char *src)
{
	ft_strncpy(dst, src, ft_strlen(src));
	*(dst + ft_strlen(src)) = '\0';
	return (dst);
}
