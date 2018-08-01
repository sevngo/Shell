#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a copy of the string given as
**	argument without whitespaces at the beginning or at the end of the string.
**	Will be considered as whitespaces the following characters ’ ’, ’\n’
**	and ’\t’.
**	If `s` has no whitespaces at the beginning or at the end, the function
**	returns a copy of `s`.
**	If the allocation fails the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

static size_t	ft_lenght(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (*(s + i) == ' ' || *(s + i) == '\n' || *(s + i) == '\t')
		i++;
	while (*(s + j) == ' ' || *(s + j) == '\n' || *(s + j) == '\t')
		j--;
	return (i == ft_strlen(s) ? 0 : ft_strlen(s) - i - (ft_strlen(s) - 1 - j));
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s || !(ptr = ft_strnew(ft_lenght(s))))
		return (NULL);
	while (*(s + i) == ' ' || *(s + i) == '\n' || *(s + i) == '\t')
		i++;
	while (j < ft_lenght(s))
		*(ptr + j++) = *(s + i++);
	*(ptr + j) = '\0';
	return (ptr);
}
