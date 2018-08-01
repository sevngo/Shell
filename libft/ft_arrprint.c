#include "libft.h"

void	ft_arrprint(char **tab, char c)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_putstr(tab[i]);
			ft_putchar(c);
			i++;
		}
	}
}
