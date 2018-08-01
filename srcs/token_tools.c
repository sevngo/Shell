#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the type for a given token content.
**	If a valid type has been given (!= TOKEN_NONE), it is immediatly returned,
**	else it searchs for the correct macro to return.
**	-------------------------------------------------------------------------- +
*/

int	token_type(char *content, int type)
{
	if (type != TOKEN_NONE)
		return (type);
	else if (ft_strcmp(content, ">") == 0)
		return (TOKEN_GREAT);
	else if (ft_strcmp(content, "<") == 0)
		return (TOKEN_LESS);
	else if (ft_strcmp(content, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(content, ";") == 0)
		return (TOKEN_SEMICOLON);
	else if (ft_strcmp(content, ">>") == 0)
		return (TOKEN_DGREAT);
	else if (ft_strcmp(content, "<<") == 0)
		return (TOKEN_DLESS);
	else if (ft_strcmp(content, "<&") == 0)
		return (TOKEN_LESSAND);
	else if (ft_strcmp(content, ">&") == 0)
		return (TOKEN_GREATAND);
	else if (ft_strcmp(content, "&&") == 0)
		return (TOKEN_AND_IF);
	else if (ft_strcmp(content, "||") == 0)
		return (TOKEN_OR_IF);
	return (TOKEN_WORD);
}

/*
**	-------------------------------------------------------------------------- +
**	Adds a token (content + type) to the linked list.
**	-------------------------------------------------------------------------- +
*/

int	token_add(t_token **head, char *content, int type)
{
	t_token	*current;
	t_token	*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (EXIT_FAILURE);
	if (!(new->content = ft_strdup(content)))
		return (EXIT_FAILURE);
	new->type = token_type(content, type);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Appends the given character to the current token.
**	-------------------------------------------------------------------------- +
*/

int	token_append(t_tokenizer *data, char ch)
{
	char	*token_new;

	if (data->token)
	{
		if (!(token_new = ft_strnew(ft_strlen(data->token) + 1)))
			return (EXIT_FAILURE);
		ft_strcpy(token_new, data->token);
		*(token_new + ft_strlen(data->token)) = ch;
		ft_strdel(&data->token);
	}
	else
	{
		if (!(token_new = ft_strnew(1)))
			return (EXIT_FAILURE);
		*token_new = ch;
	}
	data->token = token_new;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Tells if the given character is equal to the first character of an operator.
**	-------------------------------------------------------------------------- +
*/

int	token_is_operator_first_char(char fc)
{
	static char op_fc[] = { '>', '<', '|', '&', 0 };
	int			i;

	i = 0;
	while (op_fc[i])
		if (op_fc[i++] == fc)
			return (TRUE);
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Tells if the given token (string) is an operator.
**	-------------------------------------------------------------------------- +
*/

int	token_is_operator(char *token)
{
	static char	*ops[] = {
	">", "<", "|", ">>", "<<", "<&", ">&", "&&", "||",
	NULL};
	int			i;

	i = 0;
	while (*(ops + i))
		if (ft_strcmp(token, *(ops + i++)) == 0)
			return (TRUE);
	return (FALSE);
}
