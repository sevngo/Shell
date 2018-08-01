#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	exit [n]
**	Cause the shell to exit.
**	-------------------------------------------------------------------------- +
*/

int	my_exit(char **args, int *status)
{
	extern char	**environ;
	int			i;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (args && args[1] && args[2])
	{
		ft_putendl("42sh: exit: too many arguments");
		return ((*status = EXIT_FAILURE));
	}
	def_term_mode(TERM_RESET);
	save_curr_line(NULL, LINE_FREE, NULL);
	hist_write(NULL, O_APPEND);
	free_hist(&g_hist);
	ft_arrfree(environ);
	if (!args || !args[1])
		exit(g_status);
	else
	{
		i = ft_atoi(args[1]);
		exit(i);
	}
}
