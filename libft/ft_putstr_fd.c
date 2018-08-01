#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Outputs the string `s` to the file descriptor `fd`.
**	-------------------------------------------------------------------------- +
*/

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
