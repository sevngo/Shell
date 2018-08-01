#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	See "2.3 Token Recognition":
**	http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
**	-------------------------------------------------------------------------- +
*/

/*
**	-------------------------------------------------------------------------- +
**	If the end of input is recognized, the current token is delimited.
**	-------------------------------------------------------------------------- +
*/

int	token_process_1(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != '\0')
		return (0);
	if (data->sq == TRUE || data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (data->token)
	{
		if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
			return (-1);
		ft_strdel(&data->token);
	}
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current token is an operator, and the current character cannot be
**	used with the current token to form an operator, the current token gets
**	delimited, and the current character is used as the start of a new token.
**	-------------------------------------------------------------------------- +
*/

int	token_process_2(t_token **head, t_tokenizer *data, char ch)
{
	char	*token_old;

	if (!data->token || token_is_operator_first_char(*data->token) == FALSE)
		return (0);
	if (data->sq == TRUE || data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (!(token_old = ft_strdup(data->token)))
		return (-1);
	if (token_append(data, ch) == EXIT_FAILURE)
		return (-1);
	if (token_is_operator(data->token) == FALSE)
	{
		if (token_add(head, token_old, TOKEN_NONE) == EXIT_FAILURE)
			return (-1);
		ft_strdel(&token_old);
		ft_strdel(&data->token);
		data->op = FALSE;
		return (0);
	}
	data->op = TRUE;
	ft_strdel(&data->token);
	data->token = token_old;
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is single-quote, the current token gets delimited,
**	and a new token is created containing every characters until the next
**	single-quote (including it). It is then delimited as a "TOKEN_SQUOTE".
**	-------------------------------------------------------------------------- +
*/

int	token_process_3(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != CH_SQUOTE)
		return (0);
	if (data->dq == TRUE || data->bs == TRUE)
		return (0);
	if (data->sq == FALSE)
	{
		if (data->token)
		{
			if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
				return (-1);
			ft_strdel(&data->token);
		}
		data->sq = TRUE;
		return (1);
	}
	if (data->token)
		if (token_add(head, data->token, TOKEN_SQUOTED) == EXIT_FAILURE)
			return (-1);
	ft_strdel(&data->token);
	data->sq = FALSE;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is double-quote, the current token gets delimited,
**	and a new token is created containing every characters until the next
**	double-quote (including it). It is then delimited as a "TOKEN_DQUOTE".
**	-------------------------------------------------------------------------- +
*/

int	token_process_4(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != CH_DQUOTE || (data->token &&
				data->token[ft_strlen(data->token) - 1] == CH_BACKSLASH))
		return (0);
	if (data->sq == TRUE || data->bs == TRUE)
		return (0);
	if (data->dq == FALSE)
	{
		if (data->token)
		{
			if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
				return (-1);
			ft_strdel(&data->token);
		}
		data->dq = TRUE;
		return (1);
	}
	if (data->token)
		if (token_add(head, data->token, TOKEN_DQUOTED) == EXIT_FAILURE)
			return (-1);
	ft_strdel(&data->token);
	data->dq = FALSE;
	return (1);
}

/*
**	-------------------------------------------------------------------------- +
**	If the current character is <backslash>, the current token gets delimited,
**	and a new token is created containing <backslash> and the character right
**	after it, unchanged. It is the delimited as a "TOKEN_BS_QUOTED".
**	-------------------------------------------------------------------------- +
*/

int	token_process_5(t_token **head, t_tokenizer *data, char ch)
{
	if (ch != CH_BACKSLASH && data->bs == FALSE)
		return (0);
	if (data->sq == TRUE || data->dq == TRUE)
		return (0);
	if (data->bs == FALSE)
	{
		if (data->token)
		{
			if (token_add(head, data->token, TOKEN_NONE) == EXIT_FAILURE)
				return (-1);
			ft_strdel(&data->token);
		}
		data->bs = TRUE;
		return (1);
	}
	if (token_append(data, ch) == EXIT_FAILURE)
		return (-1);
	if (token_add(head, data->token, TOKEN_BS_QUOTED) == EXIT_FAILURE)
		return (-1);
	ft_strdel(&data->token);
	data->bs = FALSE;
	return (1);
}
