#include "libft.h"

/*
**	-------------------------------------------------------------------------- +
**	Outputs the string `s`, with given color, to the standard output.
**	-------------------------------------------------------------------------- +
*/

void	ft_putcolor(char *s, char *color)
{
	if (ft_strcmp(color, "BLACK") == 0)
		ft_putstr(FG_BLACK);
	else if (ft_strcmp(color, "RED") == 0)
		ft_putstr(FG_RED);
	else if (ft_strcmp(color, "GREEN") == 0)
		ft_putstr(FG_GREEN);
	else if (ft_strcmp(color, "YELLOW") == 0)
		ft_putstr(FG_YELLOW);
	else if (ft_strcmp(color, "BLUE") == 0)
		ft_putstr(FG_BLUE);
	else if (ft_strcmp(color, "MAGENTA") == 0)
		ft_putstr(FG_MAGENTA);
	else if (ft_strcmp(color, "CYAN") == 0)
		ft_putstr(FG_CYAN);
	else if (ft_strcmp(color, "WHITE") == 0)
		ft_putstr(FG_WHITE);
	ft_putstr(s);
	ft_putstr(FG_RESET);
}
