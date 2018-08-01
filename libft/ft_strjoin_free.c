#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Same as ft_strjoin(), but let us decide if we want to free the content
**	of s2 (mode = 0), s1 (mode = 1), or both s1 and s2 (mode = 2).
**	-------------------------------------------------------------------------- +
*/

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*ptr;

	if (!s1 || !s2 || !(ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (mode == 0)
		ft_strdel(&s2);
	else if (mode == 1)
		ft_strdel(&s1);
	else if (mode == 2)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (ptr);
}
