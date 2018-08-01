#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Change type of remaining TOKEN_SQUOTED, TOKEN_DQUOTED and TOKEN_BS_QUOTED
**	to TOKEN_WORD.
**	-------------------------------------------------------------------------- +
*/

static void	token_change_remaining(t_token **head)
{
	t_token	*node;

	node = *head;
	while (node)
	{
		if (node->type == TOKEN_SQUOTED || node->type == TOKEN_DQUOTED
				|| node->type == TOKEN_BS_QUOTED)
			node->type = TOKEN_WORD;
		node = node->next;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Return values:
**	-1	- error occured (malloc())
**	 0	- nothing was done, continue
**	 1	- successfuly concatenated two tokens, should delete next token
**	-------------------------------------------------------------------------- +
*/

static int	token_merge_words(t_token *curr, t_token *next)
{
	char	*new_content;

	if (curr->type != TOKEN_WORD)
		return (0);
	if (next && next->type == TOKEN_WORD)
	{
		if (!(new_content = ft_strjoin(curr->content, next->content)))
			return (-1);
		ft_strdel(&curr->content);
		curr->content = new_content;
		return (1);
	}
	return (0);
}

static int	token_merge_quoted(t_token *curr, t_token *next)
{
	char	*new_content;

	if (curr->type != TOKEN_BS_QUOTED && curr->type != TOKEN_SQUOTED
			&& curr->type != TOKEN_DQUOTED)
		return (0);
	if (next && (next->type == TOKEN_WORD || next->type == TOKEN_BS_QUOTED
			|| next->type == TOKEN_SQUOTED || next->type == TOKEN_DQUOTED))
	{
		if (!(new_content = ft_strjoin(curr->content, next->content)))
			return (-1);
		ft_strdel(&curr->content);
		curr->content = new_content;
		curr->type = TOKEN_WORD;
		return (1);
	}
	else if (next && next->type == TOKEN_EOL)
		curr->type = TOKEN_WORD;
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	Concatenates TOKEN_SQUOTE, TOKEN_DQUOTE & TOKEN_BS_QUOTED with TOKEN_WORDs.
**	-------------------------------------------------------------------------- +
*/

static int	token_merge_again(t_token **head)
{
	t_token	*curr;
	int		ret;

	curr = *head;
	while (curr)
	{
		if ((ret = token_merge_words(curr, curr->next)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 0)
			curr = curr->next;
		else if (ret == 1)
		{
			token_del_node(head, curr->next);
			curr = *head;
		}
	}
	token_change_remaining(head);
	return (EXIT_SUCCESS);
}

int			token_merge(t_token **head)
{
	t_token	*curr;
	int		ret;

	curr = *head;
	while (curr)
	{
		if ((ret = token_merge_quoted(curr, curr->next)) == -1)
			return (EXIT_FAILURE);
		else if (ret == 0)
			curr = curr->next;
		else if (ret == 1)
		{
			token_del_node(head, curr->next);
			curr = *head;
		}
	}
	return (token_merge_again(head));
}
