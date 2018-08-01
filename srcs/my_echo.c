#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	echo [string ...]
**	Write arguments to the standard output.
**
**	Return EXIT_SUCCESS only.
**	-------------------------------------------------------------------------- +
*/

int	my_echo(char **args, int *status)
{
	int	i;

	i = 1;
	if (args[1])
	{
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i++ + 1])
				ft_putchar(' ');
		}
	}
	ft_putchar('\n');
	*status = 0;
	return (EXIT_SUCCESS);
}
