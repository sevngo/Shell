#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	See chapter "2.7 Redirection"
**	http://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
**	-------------------------------------------------------------------------- +
*/

/*
**	-------------------------------------------------------------------------- +
**	Handle the following redirections: `>' and `>>'.
**
**	Return values:
**	-1				-	error (such as malloc()), program should be exited
**	EXIT_FAILURE	-	error (such as dup2(), ...), execution should be avoided
**	EXIT_SUCCESS	-	everything went fine, command should be executed
**	-------------------------------------------------------------------------- +
*/

int			cmd_redir_output(t_token *prev, t_token *curr,
												t_redir **fds, t_df *df)
{
	int	fd_old;
	int	fd_save;
	int	fd_new;
	int	open_mode;

	if (prev == NULL || curr->next == NULL)
		return (sh_return("invalid/missing redirection operator"));
	fd_old = (prev->type == TOKEN_IO_NUMBER ?
			ft_atoi(prev->content) : STDOUT_FILENO);
	if ((fd_save = cmd_redir_df_get(df, fd_old)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	open_mode = (curr->type == TOKEN_GREAT ? O_TRUNC : O_APPEND);
	if ((fd_new = open(curr->next->content,
			(O_CREAT | open_mode | O_WRONLY), 0644)) == -1)
		return (sh_return("can't open() specified file"));
	if (dup2(fd_new, fd_old) == -1)
		return (sh_return("dup2(): bad file descriptor"));
	if (close(fd_new) == -1)
		return (sh_return("close(): can't close opened file descriptor"));
	return (cmd_redir_fds_add(fds, fd_old, fd_save));
}

/*
**	-------------------------------------------------------------------------- +
**	Handle the following redirections: `<' and `<<'.
**
**	Return values:
**	-1				-	error (such as malloc()), program should be exited
**	EXIT_FAILURE	-	error (such as dup2(), ...), execution should be avoided
**	EXIT_SUCCESS	-	everything went fine, command should be executed
**	-------------------------------------------------------------------------- +
*/

static int	cmd_redir_heredoc(t_token *prev, t_token *curr,
												t_redir **fds, t_df *df)
{
	int	fd_old;
	int	fd_save;
	int	fd[2];

	fd_old = (prev->type == TOKEN_IO_NUMBER ?
			ft_atoi(prev->content) : STDIN_FILENO);
	if ((fd_save = cmd_redir_df_get(df, fd_old)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	if (pipe(fd) == -1)
		return (sh_return("pipe() failed"));
	if (dup2(fd[0], fd_old) == -1)
		return (sh_return("dup2(): bad file descriptor"));
	if (close(fd[0]) == -1)
		return (sh_return("close(): can't close opened file descriptor"));
	if (write(fd[1], curr->heredoc, ft_strlen(curr->heredoc)) == -1)
		return (sh_return("write() failed"));
	ft_strdel(&curr->heredoc);
	if (close(fd[1]) == -1)
		return (sh_return("close(): can't close opened file descriptor"));
	return (cmd_redir_fds_add(fds, fd_old, fd_save));
}

int			cmd_redir_input(t_token *prev, t_token *curr,
												t_redir **fds, t_df *df)
{
	int	fd_old;
	int	fd_save;
	int	fd_new;

	if (prev == NULL || curr->next == NULL)
		return (sh_return("invalid/missing redirection operator"));
	if (curr->type == TOKEN_DLESS)
		return (cmd_redir_heredoc(prev, curr, fds, df));
	fd_old = (prev->type == TOKEN_IO_NUMBER ?
			ft_atoi(prev->content) : STDIN_FILENO);
	if ((fd_save = cmd_redir_df_get(df, fd_old)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	if ((fd_new = open(curr->next->content, O_RDONLY)) == -1)
		return (sh_return("can't open() specified file"));
	if (dup2(fd_new, fd_old) == -1)
		return (sh_return("dup2(): bad file descriptor"));
	if (close(fd_new) == -1)
		return (sh_return("close(): can't close opened file descriptor"));
	return (cmd_redir_fds_add(fds, fd_old, fd_save));
}

/*
**	-------------------------------------------------------------------------- +
**	Handle the following redirections: `>&' and `<&'.
**
**	Return values:
**	-1				-	error (such as malloc()), program should be exited
**	EXIT_FAILURE	-	error (such as dup2(), ...), execution should be avoided
**	EXIT_SUCCESS	-	everything went fine, command should be executed
**	-------------------------------------------------------------------------- +
*/

int			cmd_redir_agre(t_token *prev, t_token *curr,
											t_redir **fds, t_df *df)
{
	int	fd_old;
	int	fd_save;
	int	def;

	if (prev == NULL || curr->next == NULL)
		return (sh_return("invalid/missing redirection operator"));
	def = (curr->type == TOKEN_GREATAND ? STDOUT_FILENO : STDIN_FILENO);
	fd_old = (prev->type == TOKEN_IO_NUMBER ? ft_atoi(prev->content) : def);
	if ((fd_save = cmd_redir_df_get(df, fd_old)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	if (curr->next->type == TOKEN_IO_NUMBER)
	{
		if (dup2(ft_atoi(curr->next->content), fd_old) == -1)
			return (sh_return("dup2(): bad file descriptor"));
	}
	else if (curr->next->type == TOKEN_MINUS)
		close(fd_old);
	else
		return (sh_return("invalid/missing file descriptor"));
	return (cmd_redir_fds_add(fds, fd_old, fd_save));
}
