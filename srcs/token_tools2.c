#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Get lenght of the current substring to expand.
**	-------------------------------------------------------------------------- +
*/

void	get_substring_size(char *input, int *size)
{
	(*size)++;
	while (input[*size] && ft_isspace(input[*size]) == FALSE
			&& input[*size] != '$' && input[*size] != ':')
		(*size)++;
}

/*
**	-------------------------------------------------------------------------- +
**	Checks if token list is empty.
**	-------------------------------------------------------------------------- +
*/

int		main_token_is_empty(t_token *head)
{
	t_token	*node;

	if (head->type == TOKEN_EOL)
		return (TRUE);
	node = head;
	while (node->next)
	{
		if (ft_strisblank(node->content) == FALSE)
			return (FALSE);
		node = node->next;
	}
	return (TRUE);
}
