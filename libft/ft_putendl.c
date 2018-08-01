#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Outputs the string `s` to the standard output followed by a ’\n’.
**	-------------------------------------------------------------------------- +
*/

void	ft_putendl(char const *s)
{
	ft_putendl_fd(s, 1);
}
