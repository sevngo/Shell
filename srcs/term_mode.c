#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Saves terminal settings (mode > 0), or resets them back as it was before
**	the call to raw_term_mode() function (mode < 0).
**	-------------------------------------------------------------------------- +
*/

int	def_term_mode(int mode)
{
	static struct termios	*attr_save = NULL;

	if (mode == TERM_SAVE)
	{
		if (!(attr_save = ft_memalloc(sizeof(struct termios))))
			return (EXIT_FAILURE);
		if (tcgetattr(STDIN_FILENO, attr_save) == -1)
			return (sh_return("could not get termios"));
	}
	if (mode == TERM_RESET)
	{
		if (attr_save)
			if (tcsetattr(STDIN_FILENO, TCSANOW, attr_save) == -1)
				return (sh_return("could not set terminal"));
		if (attr_save)
			ft_free(attr_save);
		attr_save = NULL;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Saves all terminal settings & turns on raw mode for the current terminal.
**	To do so, it disables canonical input mode, echo mode & signals, and
**	changes special parameters MIN & TIME (which controls input settings)
**	-------------------------------------------------------------------------- +
*/

int	raw_term_mode(void)
{
	struct termios	attr;

	def_term_mode(TERM_SAVE);
	if (tcgetattr(STDIN_FILENO, &attr) == -1)
		return (sh_return("could not get termios"));
	attr.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	attr.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
	attr.c_oflag |= (CS8);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) == -1)
		return (sh_return("could not set terminal"));
	return (EXIT_SUCCESS);
}
