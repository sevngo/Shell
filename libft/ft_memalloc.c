#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Allocates (with malloc(3)) and returns a “fresh” memory area.
**	The memory allocated is initialized to 0.
**	If the allocation fails, the function returns NULL.
**	-------------------------------------------------------------------------- +
*/

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
