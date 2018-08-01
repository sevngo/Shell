#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Prints a bold-italic-cyan "CHECK!". Useful when debugging code.
**	-------------------------------------------------------------------------- +
*/

void	ft_check(void)
{
	ft_putstr(FG_YELLOW);
	ft_putstr("CHECK!");
	ft_putstr(C_RESET);
	ft_putchar('\n');
}
