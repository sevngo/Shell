#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	man 3 strnstr
**	-------------------------------------------------------------------------- +
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*ptr1;
	const char	*ptr2;

	i = -1;
	ptr1 = NULL;
	ptr2 = NULL;
	while (*big && ++i < len)
	{
		j = i - 1;
		ptr1 = big;
		ptr2 = little;
		while (*ptr1 == *ptr2 && *ptr1 && *ptr2 && ++j < len)
		{
			ptr1++;
			ptr2++;
		}
		if (*ptr2 == '\0')
			return ((char *)big);
		big++;
	}
	return (!(ft_strlen(big)) && !(ft_strlen(little)) ? "" : NULL);
}
