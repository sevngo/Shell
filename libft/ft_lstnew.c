#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” link.
**	The variables `content` and `content_size` of the new link are initialized
**	by copy of the parameters of the function.
**	If the parameter content is null, the variable content is initialized to
**	NULL and the variable content_size is initialized to 0 even if the
**	parameter content_size isn’t.
**	The variable next is initialized to NULL.
**	If the allocation fails, the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	if (!(ptr = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
	}
	else
	{
		if (!(ptr->content = ft_memalloc(content_size)))
		{
			ft_free(ptr);
			return (NULL);
		}
		ft_memcpy(ptr->content, content, content_size);
		ptr->content_size = content_size;
	}
	ptr->next = NULL;
	return (ptr);
}
