#include "libft.h"

int			ft_wstrlen(wchar_t *wstr)
{
	int		n;

	n = 0;
	if (!wstr)
		return (0);
	while (*wstr)
		n += ft_wcharlen(*wstr++);
	return (n);
}
