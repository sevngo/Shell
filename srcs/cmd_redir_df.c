#include "../incs/minishell.h"

int		cmd_redir_df_get(t_df *df, int val)
{
	if (val == STDIN_FILENO)
		return (df->in);
	if (val == STDOUT_FILENO)
		return (df->out);
	if (val == STDERR_FILENO)
		return (df->err);
	return (dup(val));
}

void	cmd_redir_df_res(t_df *df)
{
	close(df->in);
	close(df->out);
	close(df->err);
}

int		cmd_redir_df_set(t_df *df)
{
	if ((df->in = dup(STDIN_FILENO)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	if ((df->out = dup(STDOUT_FILENO)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	if ((df->err = dup(STDERR_FILENO)) == -1)
		return (sh_return("dup(): bad file descriptor"));
	return (EXIT_SUCCESS);
}
