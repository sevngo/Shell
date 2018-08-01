#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Outputs the char `c` to the file descriptor `fd`.
**	-------------------------------------------------------------------------- +
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, STDOUT_FILENO);
}
