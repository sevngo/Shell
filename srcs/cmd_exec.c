#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Tells if `cmd` is a builtin command.
**	-------------------------------------------------------------------------- +
*/

static int	cmd_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "setenv") == 0 ||
		ft_strcmp(cmd, "unsetenv") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "history") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles execution of builtins in piped commands.
**	Return values:
**	-1				- error, should exit program
**	EXIT_SUCCESS	- command is a builtin
**	EXIT_FAILURE	- command is not a builtin
**	-------------------------------------------------------------------------- +
*/

int			cmd_exec_p_builtins(char **cmd, t_token *token)
{
	int	status;

	status = EXIT_SUCCESS;
	if (cmd_is_builtin(cmd[0]) == FALSE)
		return (EXIT_FAILURE);
	if (cmd_redir(token, REDIR_INIT) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if (ft_strcmp(cmd[0], "echo") == 0)
		my_echo(cmd, &status);
	else if (ft_strcmp(cmd[0], "env") == 0)
		my_env(cmd, &status);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		my_setenv(cmd, &status);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		my_unsetenv(cmd, &status);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		my_cd(cmd, &status);
	else if (ft_strcmp(cmd[0], "history") == 0)
		my_history(cmd, &status);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		my_exit(cmd, &status);
	cmd_redir(token, REDIR_RESET);
	exit(status);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles execution of builtins in simple commands.
**	Return values:
**	-1				- error, should exit program
**	EXIT_SUCCESS	- command is a builtin
**	EXIT_FAILURE	- command is not a builtin
**	-------------------------------------------------------------------------- +
*/

static int	cmd_exec_s_builtins(char **cmd, t_token *token, int *status)
{
	int	ret;

	if (cmd_is_builtin(cmd[0]) == FALSE)
		return (EXIT_FAILURE);
	if ((ret = cmd_redir(token, REDIR_INIT) != EXIT_SUCCESS))
		return (ret == -1 ? -1 : EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ret = my_echo(cmd, status);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ret = my_env(cmd, status);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ret = my_setenv(cmd, status);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ret = my_unsetenv(cmd, status);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ret = my_cd(cmd, status);
	else if (ft_strcmp(cmd[0], "history") == 0)
		ret = my_history(cmd, status);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ret = my_exit(cmd, status);
	cmd_redir(token, REDIR_RESET);
	return (ret == -1 ? -1 : EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles execution of simple commands.
**	Returns EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int			cmd_exec_s(char **cmd, t_token *token, int *status)
{
	pid_t	pid;
	int		ret;

	if ((ret = cmd_exec_s_builtins(cmd, token, status)) != EXIT_FAILURE)
		return (ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
	pid = fork();
	signal(SIGINT, sig_exe);
	if (pid == -1)
		return (sh_return("fork() failed"));
	else if (pid == 0)
		cmd_exec(cmd, token);
	return (waitpid(pid, status, 0) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles redirections, path research & execution.
**	-------------------------------------------------------------------------- +
*/

void		cmd_exec(char **cmd, t_token *token)
{
	extern char	**environ;
	char		*path;
	int			ret;

	path = NULL;
	if ((ret = cmd_redir(token, REDIR_INIT)) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if ((ret = cmd_get_path(cmd[0], &path)) == -1)
	{
		cmd_redir(token, REDIR_RESET);
		exit(EXIT_FAILURE);
	}
	else if (cmd_check_perm(cmd[0], path, ret) == 0)
	{
		cmd_redir(token, REDIR_RESET);
		exit(127);
	}
	if (execve(path, cmd, environ) == -1)
		cmd_err_msg(cmd[0]);
	ft_strdel(&path);
	cmd_redir(token, REDIR_RESET);
	exit(127);
}
