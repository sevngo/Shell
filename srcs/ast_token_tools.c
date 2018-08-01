#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Creates an array of string containing the tokens content.
**	-------------------------------------------------------------------------- +
*/

static int		is_ok_command(t_token *prev, t_token *curr)
{
	if (curr->type == TOKEN_IO_NUMBER || curr->type == TOKEN_MINUS ||
		curr->type == TOKEN_GREAT || curr->type == TOKEN_LESS ||
		curr->type == TOKEN_DGREAT || curr->type == TOKEN_DLESS ||
		curr->type == TOKEN_GREATAND || curr->type == TOKEN_LESSAND)
		return (FALSE);
	else if (prev && (prev->type == TOKEN_GREAT || prev->type == TOKEN_DGREAT
					|| prev->type == TOKEN_LESS || prev->type == TOKEN_DLESS))
		return (FALSE);
	return (TRUE);
}

static int		count_ok_tokens(t_token *head)
{
	t_token	*prev;
	t_token	*curr;
	int		len;

	len = 0;
	prev = NULL;
	curr = head;
	while (curr)
	{
		if (is_ok_command(prev, curr) == TRUE)
			len++;
		prev = curr;
		curr = curr->next;
	}
	return (len);
}

char			**token_into_array(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;
	char	**ret;
	int		i;

	if (!(ret = ft_memalloc(sizeof(char *) * (count_ok_tokens(tokens) + 1))))
		return (NULL);
	i = 0;
	prev = NULL;
	curr = tokens;
	while (curr)
	{
		if (is_ok_command(prev, curr) == TRUE)
		{
			if (!(*(ret + i) = ft_strdup(curr->content)))
				return (NULL);
			i++;
		}
		prev = curr;
		curr = curr->next;
	}
	*(ret + i) = NULL;
	return (ret);
}
