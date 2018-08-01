#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	See "2.3 Token Recognition":
**	http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
**	-------------------------------------------------------------------------- +
*/

/*
**	-------------------------------------------------------------------------- +
**	If the current character can be used as the first character of a new
**	operator, the current token (if any) shall be delimited.
**	The current character shall be used as the beginning of the next (operator)
**	token.
**	-------------------------------------------------------------------------- +
*/

int	token_process_6(t_token **head, t_tokenizer *data, char ch)
{
	if (token_is_operator_first_char(ch) == FALSE)
		return (0);
	if (data->sq == TRUE || data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (!data->token || data->op == TRUE)
		return (0);
	if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
		return (-1);
	ft_strdel(&data->token);
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is a <semicolon>, any token containing the previous
**	character is delimited and the current character is delimited as a
**	"TOKEN_SEMICOLON".
**	-------------------------------------------------------------------------- +
*/

int	token_process_7(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != CH_SEMICOLON)
		return (0);
	if (data->sq == TRUE || data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (data->token)
	{
		if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
			return (-1);
		ft_strdel(&data->token);
	}
	if (token_append(data, ch) == EXIT_FAILURE)
		return (-1);
	if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
		return (-1);
	ft_strdel(&data->token);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is a <blank>, any token containing the previous
**	character is delimited and the current character shall be discarded.
**	-------------------------------------------------------------------------- +
*/

int	token_process_8(t_token **head, t_tokenizer *data, char ch)
{
	if (ft_isspace(ch) == FALSE)
		return (0);
	if (data->sq == TRUE || data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (data->token)
	{
		if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
			return (-1);
		ft_strdel(&data->token);
	}
	if (token_add(head, ch == '\n' ? "\n" : " ", TOKEN_BLANK) == EXIT_FAILURE)
		return (-1);
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is a '#', it and all subsequent characters up to
**	shall be discarded as a comment.
**	Returns 2 to tell the main loop to break, as we don't need to do anything
**	more.
**	-------------------------------------------------------------------------- +
*/

int	token_process_9(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != '#')
		return (0);
	if (data->token)
	{
		if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
			return (-1);
		ft_strdel(&data->token);
	}
	return (2);
}

/*
**	-------------------------------------------------------------------------- +
**	If none of the previous rules has been applied, simply appends the
**	current character to the current token.
**	-------------------------------------------------------------------------- +
*/

int	token_process_10(t_token **head, t_tokenizer *data, char ch)
{
	(void)head;
	if (token_append(data, ch) == EXIT_FAILURE)
		return (-1);
	return (0);
}
