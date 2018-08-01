#include "libft.h"

char	*ft_strjoin_separator(char *prefix, char *suffix, char *separator,
									int f)
{
	char	*tmp;
	char	*final;

	if (!prefix)
		return (ft_strdup(suffix));
	if (!(tmp = ft_strjoin(prefix, separator)))
		return (NULL);
	if (!suffix)
		return (tmp);
	if (!(final = ft_strjoin(tmp, suffix)))
		return (NULL);
	if (f == 1)
		ft_strdel(&prefix);
	else if (f == 2)
		ft_strdel(&suffix);
	else if (f == 3)
	{
		ft_strdel(&prefix);
		ft_strdel(&suffix);
	}
	ft_strdel(&tmp);
	return (final);
}
