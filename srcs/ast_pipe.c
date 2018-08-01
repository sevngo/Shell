#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Return the number of cmd in pipe list.
**	-------------------------------------------------------------------------- +
*/

static int		count_cmd(t_ast *ast)
{
	int		x;

	x = 0;
	while (ast->right && ast->right->token->type == TOKEN_PIPE)
	{
		x++;
		ast = ast->right;
	}
	x = x + 3;
	return (x);
}

/*
**	-------------------------------------------------------------------------- +
**	Create an array of string containing every cmd in pipe list.
**	-------------------------------------------------------------------------- +
*/

static char		***get_pipe_array(t_ast *ast)
{
	char	***cmd;
	int		x;

	x = 0;
	if (!(cmd = ft_memalloc(sizeof(cmd) * count_cmd(ast))))
		return (NULL);
	while (ast)
	{
		if (ast->left && ast->left->token->type == TOKEN_WORD)
		{
			if (!(cmd[x] = token_into_array(ast->left->token)))
				return (NULL);
			x++;
		}
		if (ast->right && ast->right->token->type == TOKEN_WORD)
		{
			if (!(cmd[x] = token_into_array(ast->right->token)))
				return (NULL);
			x++;
			break ;
		}
		ast = ast->right;
	}
	cmd[x] = NULL;
	return (cmd);
}

/*
**	-------------------------------------------------------------------------- +
**	Copy the address of the token list for each cmd in pipe list.
**	-------------------------------------------------------------------------- +
*/

static t_token	**get_pipe_tokens(t_ast *ast)
{
	t_token	**tlist;
	int		x;

	x = 0;
	if (!(tlist = ft_memalloc(sizeof(t_token *) * count_cmd(ast))))
		return (NULL);
	while (ast)
	{
		if (ast->left && ast->left->token->type == TOKEN_WORD)
		{
			tlist[x] = ast->left->token;
			x++;
		}
		if (ast->right && ast->right->token->type == TOKEN_WORD)
		{
			tlist[x] = ast->right->token;
			x++;
			break ;
		}
		ast = ast->right;
	}
	tlist[x] = NULL;
	return (tlist);
}

/*
**	-------------------------------------------------------------------------- +
**	Send `char ***cmd` to cmd_exec_pipe(), and stock last process exit status.
**	-------------------------------------------------------------------------- +
*/

int				ast_pipe(t_ast *ast)
{
	char	***cmd;
	t_token	**token;
	int		i;

	ast->ret = EXIT_SUCCESS;
	if (!(token = get_pipe_tokens(ast)))
		return (EXIT_FAILURE);
	if (!(cmd = get_pipe_array(ast)))
		return (EXIT_FAILURE);
	if ((cmd_exec_p(cmd, token, &(ast->ret))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd[i])
		ft_arrfree(cmd[i++]);
	ft_free(cmd);
	ft_free(token);
	g_status = ast->ret;
	return (EXIT_SUCCESS);
}
