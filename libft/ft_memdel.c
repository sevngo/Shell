#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Takes as a parameter the address of a memory area that needs to be freed
**	with free(3), then puts the pointer to NULL.
**	-------------------------------------------------------------------------- +
*/

void	ft_memdel(void **ap)
{
	if (!ap || !*ap)
		return ;
	ft_free(*ap);
	*ap = NULL;
}
