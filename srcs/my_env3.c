#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Replaces environment entries.
**
**	Return values:
**	-1				- error
**	EXIT_SUCCESS	- entry already exists and has been replaced
**	EXIT_FAILURE	- entry does not exist
**	-------------------------------------------------------------------------- +
*/

static int	my_env_replace(char ***env, char *name, char *value)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(name);
	if (!(*env) || n == 0)
		return (EXIT_FAILURE);
	while ((*env)[i])
	{
		if (((ft_strncmp(name, (*env)[i], n) == 0) && (*env)[i][n] == '='))
		{
			ft_strdel(&((*env)[i]));
			if (!((*env)[i] = ft_strnew(n + 1 + ft_strlen(value))))
				return (-1);
			ft_strcpy((*env)[i], name);
			(*env)[i][n] = '=';
			ft_strcpy(&((*env)[i][n + 1]), value);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

/*
**	-------------------------------------------------------------------------- +
**	Adds new environment entries.
**	-------------------------------------------------------------------------- +
*/

int			my_env_append(char ***env, char *name, char *value)
{
	char	**tmp;
	int		ret;
	int		i;
	int		n;

	if ((n = ft_strlen(name)) == 0)
		return (EXIT_SUCCESS);
	if ((ret = my_env_replace(env, name, value)) != EXIT_FAILURE)
		return (ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
	if (!(tmp = ft_arrndup(*env, 1)))
		return (EXIT_FAILURE);
	i = 0;
	while (tmp[i])
		i++;
	if (!(tmp[i] = ft_strnew(n + 1 + ft_strlen(value))))
		return (EXIT_FAILURE);
	ft_strcpy(tmp[i], name);
	tmp[i][n] = '=';
	ft_strcpy(&(tmp[i][n + 1]), value);
	ft_arrfree(*env);
	*env = tmp;
	return (EXIT_SUCCESS);
}
