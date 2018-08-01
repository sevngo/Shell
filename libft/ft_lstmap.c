#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Iterates a list `lst` and applies the function `f` to each link to create
**	a “fresh” list (using malloc(3)) resulting from the successive applications
**	of `f`.
**	If the allocation fails, the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr1;
	t_list	*ptr2;

	if (!lst)
		return (NULL);
	ptr2 = f(lst);
	ptr1 = ptr2;
	while (lst->next)
	{
		lst = lst->next;
		if (!(ptr2->next = f(lst)))
		{
			ft_free(ptr2->next);
			return (NULL);
		}
		ptr2 = ptr2->next;
	}
	return (ptr1);
}
