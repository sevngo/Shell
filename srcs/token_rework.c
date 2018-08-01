#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Remove given `node` from linked list.
**	-------------------------------------------------------------------------- +
*/

void		token_del_node(t_token **head, t_token *node)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*tmp;

	if (node == *head)
	{
		tmp = *head;
		*head = (*head)->next;
	}
	prev = *head ? *head : NULL;
	curr = *head ? (*head)->next : NULL;
	while (prev && curr)
	{
		if (node == curr)
		{
			tmp = curr;
			prev->next = curr->next;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	ft_strdel(&tmp->content);
	ft_free(tmp);
}

/*
**	-------------------------------------------------------------------------- +
**	Remove nodes that are useless after all changes have been done.
**	-------------------------------------------------------------------------- +
*/

void		token_del_some(t_token **head, int type)
{
	t_token	*node;
	t_token	*tmp;

	node = *head;
	while (node)
	{
		tmp = node->next;
		if (node->type == type)
			token_del_node(head, node);
		node = tmp;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Change type of current token to TOKEN_MINUS if
**	- it is composed of minus (`-') character only
**	- it precedes a TOKEN_LESSAND or TOKEN_GREATAND
**	-------------------------------------------------------------------------- +
*/

static void	token_add_minus(t_token *prev, t_token *curr)
{
	if (prev && curr->type == TOKEN_WORD && ft_strcmp(curr->content, "-") == 0)
		if (prev->type == TOKEN_LESSAND || prev->type == TOKEN_GREATAND)
			curr->type = TOKEN_MINUS;
}

/*
**	-------------------------------------------------------------------------- +
**	Change type of current token to TOKEN_IO_NUMBER if
**	- it is composed of digits only
**	- it is next to OR precedes a redirection token
**	-------------------------------------------------------------------------- +
*/

static void	token_add_io_number(t_token *prev, t_token *curr, t_token *next)
{
	int	i;

	i = 0;
	while (curr->content[i])
		if (ft_isdigit(curr->content[i++]) == FALSE)
			return ;
	if (prev && (prev->type == TOKEN_GREATAND || prev->type == TOKEN_LESSAND))
		curr->type = TOKEN_IO_NUMBER;
	else if (next && (next->type == TOKEN_GREAT || next->type == TOKEN_LESS
				|| next->type == TOKEN_DGREAT || next->type == TOKEN_DLESS
				|| next->type == TOKEN_GREATAND || next->type == TOKEN_LESSAND))
		curr->type = TOKEN_IO_NUMBER;
}

/*
**	-------------------------------------------------------------------------- +
**	Change the type of certain tokens, which are defined by their previous or
**	next token type.
**	-------------------------------------------------------------------------- +
*/

int			token_rework(t_token **head)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		token_add_io_number(prev, curr, curr->next);
		token_add_minus(prev, curr);
		prev = curr;
		curr = curr->next;
	}
	if (token_expand(head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (token_merge(head) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	token_del_some(head, TOKEN_BLANK);
	return (EXIT_SUCCESS);
}
