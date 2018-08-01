#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Frees a pointer of any type, and sets it to NULL.
**	-------------------------------------------------------------------------- +
*/

void	ft_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}
