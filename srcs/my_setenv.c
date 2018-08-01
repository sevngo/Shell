#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Checks if a builtin argument contains only alphanumeric characters.
**	-------------------------------------------------------------------------- +
*/

int			arg_is_alnum(char *arg, char *name)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == FALSE)
		{
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putstr_fd(": variable name must contain ", STDERR_FILENO);
			ft_putendl_fd("alphanumeric characters", STDERR_FILENO);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/*
**	-------------------------------------------------------------------------- +
**	Checks if name contains alphanumeric characters only, and if value does not
**	contain any equal (`=') character.
**	-------------------------------------------------------------------------- +
*/

static int	check_args(char **args)
{
	int	i;

	i = 0;
	if (arg_is_alnum(args[1], "setenv") == FALSE)
		return (EXIT_FAILURE);
	else if (args[2] && ft_strchr(args[2], '='))
	{
		ft_putendl_fd("42sh: setenv: can't contain '=' character",
				STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	setenv name[=word]
**	Change or add an environment variable.
**
**	Return -1, EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int			my_setenv(char **args, int *status)
{
	extern char	**environ;

	if (ft_arrlen(args) > 3)
	{
		ft_putendl_fd("42sh: setenv: too many arguments", STDERR_FILENO);
		return ((*status = 1));
	}
	else if (ft_arrlen(args) == 1)
	{
		ft_arrprint(environ, '\n');
		return ((*status = 0));
	}
	if (check_args(args) == EXIT_FAILURE)
		return ((*status = 1));
	if (env_append(args[1], args[2] ? args[2] : "") == EXIT_FAILURE)
		return ((*status = -1));
	return ((*status = 0));
}
