#include "../incs/minishell.h"

/*
** https://www.gnu.org/software/bash/manual/html_node/Bash-History-Builtins.html
** https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html
*/

/*
**	-------------------------------------------------------------------------- +
**	history -awrn [filename]
**	-a	Append the ``new'' history lines (history lines entered since the
**		beginning of the current 42sh session) to the history file.
**	-w	Write the current history to the history file, overwriting the history
**		file's contents.
**	-r	Read the history file and append its contents to the history list.
**	-n	Append the history lines not already read from the history file to the
**		current history list. These are lines appended to the history file
**		since the beginning of the current 42sh session.
**
**	If `filename` is given, then that is used as the history file, else if
**	$HISTFILE has a value, that is used, else ~/.42sh_history.
**	-------------------------------------------------------------------------- +
*/

int	hist_opta(char **args)
{
	if (args[2])
		return (hist_write(args[2], O_APPEND));
	return (hist_write(NULL, O_APPEND));
}

int	hist_optw(char **args)
{
	if (args[2])
		return (hist_write(args[2], O_TRUNC));
	return (hist_write(NULL, O_TRUNC));
}

int	hist_optr(char **args)
{
	char	*histfile;
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	if (args[2])
		histfile = args[2];
	else
		histfile = env_get_val("HISTFILE") ? env_get_val("HISTFILE") : HISTFILE;
	if ((fd = open(histfile, O_RDONLY)) == -1)
		return (sh_return("can't open history file"));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		hist_append(&g_hist, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (ret == -1 ? ret : EXIT_SUCCESS);
}

int	hist_optn(char **args)
{
	char	*histfile;
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	if (args[2])
		histfile = args[2];
	else
		histfile = env_get_val("HISTFILE") ? env_get_val("HISTFILE") : HISTFILE;
	if ((fd = open(histfile, O_RDONLY)) == -1)
		return (sh_return("can't open history file"));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (hist_exists(line) == FALSE)
			hist_append(&g_hist, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (ret = -1 ? ret : EXIT_SUCCESS);
}
