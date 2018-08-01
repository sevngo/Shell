#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Checks if arguments are valid, and add entries to builtin environment.
**	-------------------------------------------------------------------------- +
*/

static int	create_entry(char *str, int i, char **name, char **value)
{
	if (i == 0)
	{
		ft_putendl_fd("42sh: env: invalid argument: `='", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!(*name = ft_strndup(str, i)))
		return (-1);
	if (arg_is_alnum(*name, "env") == FALSE)
	{
		ft_strdel(&*name);
		return (EXIT_FAILURE);
	}
	if (!(*value = ft_strdup(&(str[i + 1]))))
		return (-1);
	return (EXIT_SUCCESS);
}

static int	is_utility(char ***env, char *str, int i)
{
	char	*name;
	char	*value;
	int		ret;

	if (str[0] == '-')
		return (EXIT_SUCCESS);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if ((ret = create_entry(str, i, &name, &value)) != EXIT_SUCCESS)
				return (ret);
			if (my_env_append(env, name, value) == EXIT_FAILURE)
				return (-1);
			ft_strdel(&name);
			ft_strdel(&value);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (2);
}

/*
**	-------------------------------------------------------------------------- +
**	Displays "illegal option" error message, and returns EXIT_SUCCESS.
**	-------------------------------------------------------------------------- +
*/

static int	env_error(char c)
{
	ft_putstr_fd("42sh: env: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd("usage: env [-i] [name=value]... [utility [argument...]]",
			STDERR_FILENO);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Checks the arguments given to `env` builtin.
**	-------------------------------------------------------------------------- +
*/

static int	env_check_opt(char **args, int *opt)
{
	int		i;
	int		l;

	i = 1;
	*opt = 1;
	while (args[i])
	{
		if (args[i][0] != '-')
			break ;
		else
		{
			l = 1;
			while (args[i][l])
			{
				if (args[i][l] == 'i')
					*opt = 0;
				else
					return (env_error(args[i][l]));
				l++;
			}
		}
		i++;
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	env [-i] [name=value]... [utility [argument...]]
**	Set the environment for command invocation.
**	-------------------------------------------------------------------------- +
*/

int			my_env(char **args, int *status)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			ret;

	ret = 0;
	env = NULL;
	if (env_check_opt(args, &i) == EXIT_SUCCESS)
	{
		*status = 1;
		return (EXIT_SUCCESS);
	}
	if (i == 1)
		if (!(env = ft_arrdup(environ)))
			return (-1);
	i = 1;
	while (args[i] && (ret = is_utility(&env, args[i], 0)) == EXIT_SUCCESS)
		i++;
	if (ret == EXIT_SUCCESS)
		ft_arrprint(env, '\n');
	else if (ret == 2)
		return ((i = my_env_exec(&args[i], status, env)));
	ft_arrfree(env);
	return (ret);
}
