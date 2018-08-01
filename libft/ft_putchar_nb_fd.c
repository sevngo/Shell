#include "libft.h"

void	ft_putchar_nb_fd(int fd, char c, int size)
{
	int x;

	x = 0;
	while (x < size)
	{
		write(fd, &c, 1);
		x++;
	}
}
