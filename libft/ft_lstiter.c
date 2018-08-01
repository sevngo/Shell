#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Iterates the list `lst` and applies the function `f` to each link.
**	-------------------------------------------------------------------------- +
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (!lst)
		return ;
	f(lst);
	ft_lstiter(lst->next, f);
}
