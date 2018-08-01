#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns an array of “fresh” strings
**	(all ending with ’\0’, including the array itself) obtained by spliting `s`
**	using the character `c` as a delimiter.
**	If the allocation fails the function returns NULL.
**
**	Example : ft_strsplit("*hello*fellow***students*", ’*’) returns the array
**	["hello", "fellow", "students"].
**	-------------------------------------------------------------------------- +
*/

static int	get_word_len(char const *s, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (*(s + i) && *(s + i) == c)
		i++;
	while (*(s + i) && *(s + i) != c)
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s || !(arr = ft_memalloc(sizeof(char *) *
					(ft_nbofwords((char *)s, c) + 1))))
		return (NULL);
	while (i < ft_nbofwords((char *)s, c))
	{
		k = 0;
		if (!(*(arr + i) = ft_strnew(get_word_len(&s[j], c) + 1)))
			return (NULL);
		while (*(s + j) && *(s + j) == c)
			j++;
		while (*(s + j) && *(s + j) != c)
			arr[i][k++] = *(s + j++);
		arr[i][k] = '\0';
		i++;
	}
	*(arr + i) = NULL;
	return (arr);
}
