#include "../incs/minishell.h"

static int		change_dir(char *curpath, char *dir, char opt)
{
	char	*cwd;

	cwd = NULL;
	if (!curpath)
		return (1);
	if (chdir(curpath))
		return (1);
	env_append("OLDPWD", env_get_val("PWD"));
	if (opt == 'P')
	{
		env_append("PWD", cwd = getcwd(NULL, 0));
		ft_strdel(&cwd);
	}
	else
		env_append("PWD", curpath);
	if (dir && ft_strequ(dir, "-"))
		ft_printf("%s\n", env_get_val("PWD"));
	return (0);
}

static char		*convert_curpath(char *curpath)
{
	char		*tmp;
	char		*cwd;

	tmp = NULL;
	cwd = NULL;
	if (curpath[0] != '/')
	{
		if (!(tmp = env_get_val("PWD")))
		{
			cwd = getcwd(NULL, 0);
			tmp = cwd;
		}
		if (tmp && tmp[ft_strlen(tmp) - 1] == '/')
			tmp = ft_strjoin(tmp, curpath);
		else if (tmp)
			tmp = ft_strcjoin(tmp, curpath, '/');
		ft_strdel(&curpath);
		ft_strdel(&cwd);
		curpath = tmp;
	}
	curpath = simplify_path(curpath);
	return (curpath);
}

static int		handle_error(char *curpath)
{
	struct stat pathstat;

	if (!stat(curpath, &pathstat) && !S_ISDIR(pathstat.st_mode))
	{
		ft_printf("%wcd: %s: %s\n", 2, EMNOTDIR, curpath);
		return (1);
	}
	if (-1 == access(curpath, F_OK))
	{
		ft_printf("%wcd: %s: %s\n", 2, EMNOENT, curpath);
		return (1);
	}
	if (-1 == access(curpath, R_OK))
	{
		ft_printf("%wcd: %s: %s\n", 2, EMACCES, curpath);
		return (1);
	}
	return (0);
}

static char		*get_curpath(char *dir)
{
	char		*curpath;

	if (!dir && !(dir = env_get_val("HOME")))
	{
		ft_printf("%wcd : %s not set\n", 2, "HOME");
		return (NULL);
	}
	else if (ft_strequ(dir, "-") && !(dir = env_get_val("OLDPWD")))
	{
		ft_printf("%wcd : %s not set\n", 2, "OLDPWD");
		return (NULL);
	}
	if ((dir[0] == '/') || (dir[0] == '.' && (dir[1] == '/' || !dir[1])) ||
			(ft_strnequ(dir, "..", 2) || (dir[2] == '/' || !dir[2])))
		curpath = ft_strdup(dir);
	else if (!(curpath = get_envpathentry(dir, "CDPATH")))
		curpath = ft_strdup(dir);
	return (curpath);
}

int				my_cd(char **args, int *status)
{
	char		*curpath;
	char		opt;
	int			i;
	int			exitcode;

	i = 0;
	opt = 0;
	curpath = NULL;
	while (args[++i] && (ft_strequ(args[i], "-P") || ft_strequ(args[i], "-L")))
		opt = args[i][1];
	if (!(curpath = get_curpath(args[i])))
		return ((*status = 1));
	if (!(exitcode = handle_error(curpath)))
	{
		if (opt != 'P')
			curpath = convert_curpath(curpath);
		exitcode = change_dir(curpath, args[i], opt);
	}
	ft_strdel(&curpath);
	return ((*status = exitcode));
}
