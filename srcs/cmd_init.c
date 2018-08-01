#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles errors message if execve fails.
**	-------------------------------------------------------------------------- +
*/

void	cmd_err_msg(char *cmd)
{
	struct stat	buf;

	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (stat(cmd, &buf) == 0 && S_ISDIR(buf.st_mode))
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (*cmd == '/')
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles errors display if the path cannot be found or permission is denied.
**	1	- success (no problemo)
**	0	- failure (permission error/command not found)
**	-------------------------------------------------------------------------- +
*/

int		cmd_check_perm(char *cmd, char *path, int ret)
{
	if (ret == 0 || access(path, F_OK) == -1)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		if (*cmd == '/')
			ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		else
			ft_putendl_fd(": command not found", STDERR_FILENO);
		if (ret != 0)
			ft_strdel(&path);
		return (0);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
		ft_strdel(&path);
		return (0);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the full path of a command, or an error code (see below);
**	 1	- success (full path found)
**	 0	- failure (path not found)
**	-1	- error
**	-------------------------------------------------------------------------- +
*/

int		cmd_get_path(char *cmd, char **path)
{
	char	**paths;
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	if (*cmd == '/' || *cmd == '.' || ft_strncmp(cmd, "..", 2) == 0)
		return (!(*path = ft_strdup(cmd)) ? -1 : 1);
	if (!env_get_val("PATH") || ft_strisblank(env_get_val("PATH")) == TRUE)
		return (0);
	if (!(paths = ft_strsplit(env_get_val("PATH"), ':')))
		return (-1);
	while (*(paths + i))
	{
		if (!(tmp = ft_strjoin(*(paths + i), "/")))
			return (-1);
		if (!(ret = ft_strjoin_free(tmp, cmd, 1)))
			return (-1);
		if (access(ret, F_OK) == 0)
			break ;
		ft_strdel(&ret);
		i++;
	}
	ft_arrfree(paths);
	return ((*path = ret) ? 1 : 0);
}
