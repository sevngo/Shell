#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Replace a part of a string delimited by [st;sp] included.
**	-------------------------------------------------------------------------- +
*/

char	*ft_strepart(char *str, char *rep, int st, int sp)
{
	char	*str1;
	char	*str2;
	char	*ret;

	if (!str || !rep || st < 0 || sp - st > (int)ft_strlen(str))
		return (str);
	if (!(str1 = ft_strsub(str, 0, st)))
		return (NULL);
	if (!(str2 = ft_strsub(str, sp + 1, ft_strlen(str) - sp)))
		return (NULL);
	ft_strdel(&str);
	if (!(str = ft_strjoin_free(str1, rep, 1)))
		return (NULL);
	if (!(ret = ft_strjoin_free(str, str2, 2)))
		return (NULL);
	return (ret);
}
