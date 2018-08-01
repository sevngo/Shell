/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	eat(t_token **tlist, int token_type)
{
	if (tlist == NULL)
		return (0);
	if ((*tlist) == NULL)
		return (0);
	while ((*tlist)->type == TOKEN_BLANK)
		*tlist = (*tlist)->next;
	if ((*tlist) == NULL)
		return (0);
	if ((*tlist)->type == token_type)
	{
		*tlist = (*tlist)->next;
		return (1);
	}
	else
		return (0);
}

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_command(t_token **tlist)
{
	if (eat(tlist, TOKEN_WORD) == 0)
		return (0);
	while (42)
	{
		if (eat(tlist, TOKEN_SEMICOLON))
		{
			if (eat(tlist, TOKEN_EOL))
				return (1);
			else
				return (is_command(tlist));
		}
		if (eat(tlist, TOKEN_AND_IF) ||
							eat(tlist, TOKEN_OR_IF) || eat(tlist, TOKEN_PIPE))
			return (is_command(tlist));
		if (eat(tlist, TOKEN_EOL))
			return (1);
		if (is_command_elem(tlist) == 0)
			return (0);
	}
}

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_command_elem(t_token **tlist)
{
	if (is_word(tlist))
		return (1);
	else if (is_redirection(tlist))
		return (1);
	else
		return (0);
}

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_word(t_token **tlist)
{
	return (eat(tlist, TOKEN_WORD));
}

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_redirection(t_token **tlist)
{
	if (is_simple_redirection(tlist))
		return (1);
	else if (is_io_redirection(tlist))
		return (1);
	else if (is_io_redirection2(tlist))
		return (1);
	else if (is_io_redirection3(tlist))
		return (1);
	else if (is_close_redirection(tlist))
		return (1);
	else if (is_close_redirection2(tlist))
		return (1);
	else
		return (0);
}
