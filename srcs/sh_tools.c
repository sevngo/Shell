#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Stores screen rows & cols in integers, and returns status.
**	-------------------------------------------------------------------------- +
*/

int		get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1)
		return (sh_return("can't get window size"));
	*rows = ws.ws_row;
	*cols = ws.ws_col;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Display default shell prompt.
**	40 -> 51
**	-------------------------------------------------------------------------- +
*/

void	sh_prompt(int mode)
{
	int	color;

	if (mode == PROMPT_BASIC)
	{
		ft_putstr_fd(C_RESET, STDERR_FILENO);
		ft_putstr_fd("\033[38;5;", STDERR_FILENO);
		color = (g_status == 0 ? 82 : 124);
		ft_putnbr_fd(color, STDERR_FILENO);
		ft_putstr_fd("m", STDERR_FILENO);
		ft_putstr_fd("$> ", STDERR_FILENO);
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	}
	else if (mode == PROMPT_QUOTE)
	{
		ft_putstr_fd(C_RESET, STDERR_FILENO);
		ft_putstr_fd("> ", STDERR_FILENO);
	}
	else if (mode == PROMPT_HDOCS)
	{
		ft_putstr_fd(C_RESET, STDERR_FILENO);
		ft_putstr_fd("% ", STDERR_FILENO);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	On error, prints a message on standard error, and returns "EXIT_FAILURE".
**	eg. return (sh_return("error: invalid tty"))
**	-------------------------------------------------------------------------- +
*/

int		sh_return(char *message)
{
	if (message)
	{
		ft_putstr_fd("42sh: error: ", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	On error, prints a message on standard error, and exits with status
**	"EXIT_FAILURE".
**	eg. sh_exit("error: env_init() failed to execute")
**	-------------------------------------------------------------------------- +
*/

void	sh_exit(char *message)
{
	if (message)
	{
		ft_putstr_fd("42sh: error: ", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	free_hist(&g_hist);
	exit(EXIT_FAILURE);
}
