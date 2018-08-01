#include <libft.h>

void		ft_tabdel(char ***atab)
{
	char	**tmp;

	tmp = *atab;
	while (tmp && *tmp)
		ft_strdel(tmp++);
	ft_memdel((void*)atab);
}
