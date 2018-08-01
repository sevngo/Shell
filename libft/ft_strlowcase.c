#include <libft.h>

char		*ft_strlowcase(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		*tmp = ft_tolower((int)*tmp);
		++tmp;
	}
	return (s);
}
