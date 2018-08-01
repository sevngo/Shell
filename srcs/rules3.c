#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_close_redirection(t_token **tlist)
{
	t_token	*tmp;

	tmp = *tlist;
	if (eat(tlist, TOKEN_DLESS) && eat(tlist, TOKEN_MINUS) &&
														eat(tlist, TOKEN_WORD))
		return (1);
	else
		*tlist = tmp;
	if (eat(tlist, TOKEN_IO_NUMBER) && eat(tlist, TOKEN_DLESS) &&
							eat(tlist, TOKEN_MINUS) && eat(tlist, TOKEN_WORD))
		return (1);
	else
		*tlist = tmp;
	if (eat(tlist, TOKEN_GREATAND) && eat(tlist, TOKEN_MINUS))
		return (1);
	else
		*tlist = tmp;
	if (eat(tlist, TOKEN_IO_NUMBER) && eat(tlist, TOKEN_GREATAND) &&
														eat(tlist, TOKEN_MINUS))
		return (1);
	else
		*tlist = tmp;
	return (0);
}

/*
**	-------------------------------------------------------------------------- +
**
**	-------------------------------------------------------------------------- +
*/

int	is_close_redirection2(t_token **tlist)
{
	t_token	*tmp;

	tmp = *tlist;
	if (eat(tlist, TOKEN_LESSAND) && eat(tlist, TOKEN_MINUS))
		return (1);
	else
		*tlist = tmp;
	if (eat(tlist, TOKEN_IO_NUMBER) && eat(tlist, TOKEN_LESSAND) &&
														eat(tlist, TOKEN_MINUS))
		return (1);
	else
		*tlist = tmp;
	return (0);
}
