#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns, if existing, the value for a given `name` in the environ.
**	It does NOT return a copy of the string, but the original one.
**	-------------------------------------------------------------------------- +
*/

char		*env_get_val(char *name)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	if (!environ)
		return (NULL);
	while (environ[i])
	{
		if (ft_strncmp(name, environ[i], n) == 0 && environ[i][n] == '=')
			return (&(environ[i][n + 1]));
		i++;
	}
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Checks if 'name' is already in the environ, or not.
**	-------------------------------------------------------------------------- +
*/

int			env_entry_exists(char *name)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	if (!name || !environ || name[0] == '\0')
		return (-1);
	while (environ[i])
	{
		if ((ft_strncmp(name, environ[i], n) == 0 && environ[i][n] == '='))
			return (i);
		i++;
	}
	return (-1);
}

/*
**	-------------------------------------------------------------------------- +
**	Replaces the value of 'name' with a new value in the environ.
**	It finds the corresponding entry, deletes it, then mallocs a new string
**	able to stock : "name" + '=' + "value" + '\0', end fill it with given data.
**	-------------------------------------------------------------------------- +
*/

int			env_replace(char *name, char *value)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = ft_strlen(name);
	if (!environ)
		return (EXIT_SUCCESS);
	while (environ[i])
	{
		if (((ft_strncmp(name, environ[i], n) == 0) && environ[i][n] == '='))
		{
			ft_strdel(&(environ[i]));
			if (!(environ[i] = ft_strjoin_separator(name, value, "=", 0)))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	Appends the 'name'/'value' couple to the environ.
**	-------------------------------------------------------------------------- +
*/

int			env_append(char *name, char *value)
{
	extern char	**environ;
	char		**tmp;
	int			i;

	if (env_replace(name, value) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (!(tmp = ft_arrndup(environ, 1)))
		return (EXIT_FAILURE);
	i = 0;
	while (tmp[i])
		i++;
	if (!(tmp[i] = ft_strjoin_separator(name, value, "=", 0)))
		return (EXIT_FAILURE);
	ft_arrfree(environ);
	environ = tmp;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Removes the element called 'name' in the environ.
**	-------------------------------------------------------------------------- +
*/

int			env_remove(char *name)
{
	extern char	**environ;
	char		**tmp;
	int			i;
	int			l;
	int			x;

	if ((x = env_entry_exists(name)) == -1)
		return (EXIT_SUCCESS);
	if (!(tmp = ft_memalloc(sizeof(char *) * ft_arrlen(environ))))
		return (EXIT_FAILURE);
	i = -1;
	l = 0;
	while (environ[++i])
	{
		if (i != x)
		{
			if (!(tmp[l] = ft_strdup(environ[i])))
				return (EXIT_FAILURE);
			l++;
		}
	}
	tmp[l] = NULL;
	ft_arrfree(environ);
	environ = tmp;
	return (EXIT_SUCCESS);
}
