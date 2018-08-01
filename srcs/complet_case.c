#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	find all the possibility of completion in the corresponding path
 **	-------------------------------------------------------------------------- +
*/

char	**get_paths_tab(void)
{
	return (ft_strsplit(getenv("PATH"), ':'));
}

int		case_path(t_complet *comp)
{
	DIR				*dir;
	t_list_words	*tmp;
	char			**paths;
	int				i;

	i = 0;
	if (!(paths = get_paths_tab()))
		return (0);
	tmp = NULL;
	while (paths[i])
	{
		if ((dir = opendir(paths[i])))
		{
			get_list(comp, dir, &tmp);
			closedir(dir);
		}
		i++;
	}
	ft_arrfree(paths);
	comp->list = tmp;
	return (0);
}

int		case_pwd(t_complet *comp)
{
	DIR				*dir;
	t_list_words	*tmp;

	tmp = NULL;
	if (!comp->path || comp->path[0] == '\0')
	{
		if (!(dir = opendir(".")))
			return (0);
	}
	else if (!(dir = opendir(comp->path)))
		return (0);
	if (get_list(comp, dir, &tmp) == 0)
		return (0);
	comp->list = tmp;
	closedir(dir);
	return (0);
}

int		case_absolute(t_complet *comp)
{
	DIR				*dir;
	t_list_words	*tmp;

	tmp = NULL;
	if (!comp->path)
		return (0);
	if (!(dir = opendir(comp->path)))
		return (0);
	if (get_list(comp, dir, &tmp) == 0)
		return (0);
	comp->list = tmp;
	closedir(dir);
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	find wich case needs to be use
**	-------------------------------------------------------------------------- +
*/

int		complet_wich_case(char *input, char *last)
{
	int		i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
	{
		ft_free(last);
		return (0);
	}
	while (!ft_isspace(input[i]) && input[i])
		i++;
	if (input[i])
		return ((last[0] != '/') ? CASE_PWD : CASE_ABSOLUTE);
	else
	{
		if (ft_strchr(last, '/') == NULL)
			return (CASE_PATH);
		else
			return (((last[0] != '/')) ? CASE_PWD : CASE_ABSOLUTE);
	}
	return (0);
}
