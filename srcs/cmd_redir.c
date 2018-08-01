#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	See chapter "2.7 Redirection"
**	http://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
**	-------------------------------------------------------------------------- +
*/

/*
**	-------------------------------------------------------------------------- +
**	Reset redirections, by setting file descriptors back to their old values.
**	-------------------------------------------------------------------------- +
*/

static int	cmd_redir_reset(t_redir **fds, t_df *df)
{
	t_redir	*node;
	t_redir	*tmp;

	node = *fds;
	cmd_redir_fds_rev(&node);
	while (node)
	{
		dup2(node->save, node->old);
		close(node->save);
		tmp = node->next;
		ft_free(node);
		node = tmp;
	}
	*fds = NULL;
	cmd_redir_df_res(df);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handle the following redirections: `>', `>>', `<', `<<', `>&' and `<&'.
**
**	Return values:
**	-1				-	error (such as malloc()), program should be exited
**	EXIT_FAILURE	-	error (such as dup2(), ...), execution should be avoided
**	EXIT_SUCCESS	-	everything went fine, command should be executed
**	-------------------------------------------------------------------------- +
*/

static int	cmd_redir_call(t_token *head, t_redir **fds, t_df *df)
{
	t_token	*prev;
	t_token	*curr;
	int		ret;

	prev = NULL;
	curr = head;
	ret = EXIT_SUCCESS;
	while (curr)
	{
		if (curr->type == TOKEN_GREAT || curr->type == TOKEN_DGREAT)
			ret = cmd_redir_output(prev, curr, fds, df);
		else if (curr->type == TOKEN_LESS || curr->type == TOKEN_DLESS)
			ret = cmd_redir_input(prev, curr, fds, df);
		else if (curr->type == TOKEN_GREATAND || curr->type == TOKEN_LESSAND)
			ret = cmd_redir_agre(prev, curr, fds, df);
		if (ret == EXIT_FAILURE || ret == -1)
			return (ret);
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int			cmd_redir(t_token *head, int mode)
{
	static t_redir	*fds = NULL;
	static t_df		df;
	int				ret;

	if (mode == REDIR_RESET)
		return (fds == NULL ? EXIT_SUCCESS : cmd_redir_reset(&fds, &df));
	if (cmd_redir_df_set(&df) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = cmd_redir_call(head, &fds, &df);
	if (fds == NULL || ret != EXIT_SUCCESS)
		cmd_redir_reset(&fds, &df);
	return (ret);
}
