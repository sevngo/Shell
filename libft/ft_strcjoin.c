#include <libft.h>

char		*ft_strcjoin(char const *s1, char const *s2, char c)
{
	char	*dst;
	int		len;

	dst = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1);
		if (!(dst = ft_strnew(sizeof(char) * (len + ft_strlen(s2) + 1))))
			return (NULL);
		ft_strcpy(dst, s1);
		dst[len] = c;
		ft_strcpy(&dst[len + 1], s2);
	}
	return (dst);
}
