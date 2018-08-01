#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles errors message if execve fails.
**	-------------------------------------------------------------------------- +
*/

static void	my_env_err_msg(char *cmd)
{
	struct stat	buf;

	ft_putstr_fd("42sh: env: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (stat(cmd, &buf) == 0 && S_ISDIR(buf.st_mode))
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles errors display if the path cannot be found or permission is denied.
**	1	- success (no problemo)
**	0	- failure (permission error/command not found)
**	-------------------------------------------------------------------------- +
*/

static int	my_env_check_perm(char *cmd, char *path, int ret)
{
	if (ret == 0 || access(path, F_OK) == -1)
	{
		ft_putstr_fd("42sh: env: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		if (ret != 0)
			ft_strdel(&path);
		return (0);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("42sh: env: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
		ft_strdel(&path);
		return (0);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns, if existing, the value for a given `name` in the environment.
**	It does NOT return a copy of the string, but the original one.
**	-------------------------------------------------------------------------- +
*/

static char	*my_env_get_val(char *name, char **env)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(name);
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(name, env[i], n) == 0 && env[i][n] == '=')
		{
			if (ft_strisblank(&(env[i][n + 1])) == TRUE)
				return (NULL);
			return (&(env[i][n + 1]));
		}
		i++;
	}
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the full path of a command, or an error code (see below);
**	-1	- error
**	 0	- failure (path not found)
**	 1	- success (full path found)
**	-------------------------------------------------------------------------- +
*/

static int	my_env_get_path(char *cmd, char **path, char **env)
{
	char	**paths;
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	if (*cmd == '/' || *cmd == '.' || ft_strncmp(cmd, "..", 2) == 0)
		return (!(*path = ft_strdup(cmd)) ? -1 : 1);
	if (!my_env_get_val("PATH", env))
		return (0);
	if (!(paths = ft_strsplit(my_env_get_val("PATH", env), ':')))
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

/*
**	-------------------------------------------------------------------------- +
**	Executes the utility given to to `env` builtin.
**	-------------------------------------------------------------------------- +
*/

int			my_env_exec(char **cmd, int *status, char **env)
{
	char	*path;
	int		ret;
	pid_t	pid;

	if ((ret = my_env_get_path(cmd[0], &path, env)) == -1)
		return (-1);
	else if (my_env_check_perm(cmd[0], path, ret) == 0)
	{
		ft_arrfree(env);
		return (EXIT_FAILURE);
	}
	pid = fork();
	signal(SIGINT, sig_exe);
	if (pid == -1)
		ret = -21;
	else if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
			my_env_err_msg(cmd[0]);
		exit(EXIT_FAILURE);
	}
	ft_strdel(&path);
	ft_arrfree(env);
	return (ret == -21 || waitpid(pid, status, 0) == -1 ?
			EXIT_FAILURE : EXIT_SUCCESS);
}
