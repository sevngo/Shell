#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles pipes fildes redirections.
**	-------------------------------------------------------------------------- +
*/

static void	cmd_exec_redirect(int fd_old, int fd_new)
{
	if (fd_old != fd_new)
	{
		if (dup2(fd_old, fd_new) == -1)
			ft_putendl_fd("42sh: pipes: failed to dup2()", STDERR_FILENO);
		close(fd_old);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	-1				- error, should exit program
**	EXIT_FAILURE	- fail, should avoid execution
**	EXIT_SUCCESS	- should continue execution
**	-------------------------------------------------------------------------- +
*/

static int	cmd_exec_last(t_pipe data, int *status, size_t pos, int fd_in)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	signal(SIGINT, sig_exe);
	if (pid == -1)
		return (sh_return("fork() failed"));
	else if (pid == 0)
	{
		cmd_exec_redirect(fd_in, STDIN_FILENO);
		if ((ret = cmd_exec_p_builtins(data.cmds[pos], data.tokens[pos]))
				== EXIT_FAILURE)
			cmd_exec(data.cmds[pos], data.tokens[pos]);
	}
	close(fd_in);
	ret = waitpid(pid, status, 0);
	*status = WEXITSTATUS(*status);
	return (ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	-1				- error, should exit program
**	EXIT_FAILURE 1)	- fail, should avoid execution
**	EXIT_SUCCESS 0)	- should continue execution
**	-------------------------------------------------------------------------- +
*/

static int	cmd_exec_rest(t_pipe data, int *status, size_t pos, int fd_in)
{
	pid_t	pid;
	int		pdes[2];
	int		ret;

	if (pipe(pdes) == -1)
		return (sh_return("pipe() failed"));
	pid = fork();
	signal(SIGINT, sig_exe);
	if (pid == -1)
		return (sh_return("fork() failed"));
	else if (pid == 0)
	{
		close(pdes[READ_END]);
		cmd_exec_redirect(fd_in, STDIN_FILENO);
		cmd_exec_redirect(pdes[WRITE_END], STDOUT_FILENO);
		if ((ret = cmd_exec_p_builtins(data.cmds[pos], data.tokens[pos])) == 1)
			cmd_exec(data.cmds[pos], data.tokens[pos]);
	}
	close(pdes[WRITE_END]);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if ((ret = cmd_exec_pipe(data, status, pos + 1, pdes[READ_END])) != 0)
		return (ret);
	return (waitpid(pid, &ret, WUNTRACED) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	-1				- error, should exit program
**	EXIT_FAILURE	- fail, should avoid execution
**	EXIT_SUCCESS	- should continue execution
**	-------------------------------------------------------------------------- +
*/

int			cmd_exec_pipe(t_pipe data, int *status, size_t pos, int fd_in)
{
	int	ret;

	if (data.cmds[pos + 1] == NULL)
		return (cmd_exec_last(data, status, pos, fd_in));
	else if ((ret = cmd_exec_rest(data, status, pos, fd_in)) != EXIT_SUCCESS)
		return (ret);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles execution of piped commands.
**	Returns EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

int			cmd_exec_p(char ***cmds, t_token **tokens, int *status)
{
	t_pipe	data;

	data.cmds = cmds;
	data.tokens = tokens;
	if (cmd_exec_pipe(data, status, 0, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
