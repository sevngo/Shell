#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Execute left and stock ret, then execute right and replace current ret.
**	-------------------------------------------------------------------------- +
*/

static int	ast_semicolon(t_ast *ast)
{
	if (ast->left && ast->left->token)
		if (read_ast(ast->left) == EXIT_SUCCESS)
			ast->ret = ast->left->ret;
	if (ast->right && ast->right->token)
		if (read_ast(ast->right) == EXIT_SUCCESS)
			ast->ret = ast->right->ret;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Check if left cmd has been already executed (according to token->up);
**	- if not, then execute it
**	- if ret was 0 (ended with no error), then execute the right cmd (and
**	right->left according to his type)
**	-------------------------------------------------------------------------- +
*/

static int	ast_andif(t_ast *ast)
{
	if (ast->up && (ast->up->token->type != TOKEN_SEMICOLON))
		ast->ret = ast->up->ret;
	else
	{
		if (read_ast(ast->left) == EXIT_SUCCESS)
			ast->ret = ast->left->ret;
	}
	if (ast->right && (ast->right->token->type == TOKEN_AND_IF ||
						ast->right->token->type == TOKEN_OR_IF))
	{
		if (ast->ret == 0)
		{
			if (read_ast(ast->right->left) == EXIT_SUCCESS)
				ast->ret = ast->right->left->ret;
		}
		if (read_ast(ast->right) == EXIT_SUCCESS)
			ast->ret = ast->right->ret;
	}
	else if (ast->ret == 0)
	{
		if (read_ast(ast->right) == EXIT_SUCCESS)
			ast->ret = ast->right->ret;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Same as ast_andif, but check if ret was different than 0 (ended with error).
**	-------------------------------------------------------------------------- +
*/

static int	ast_orif(t_ast *ast)
{
	if (ast->up && (ast->up->token->type != TOKEN_SEMICOLON))
		ast->ret = ast->up->ret;
	else
	{
		if (read_ast(ast->left) == EXIT_SUCCESS)
			ast->ret = ast->left->ret;
	}
	if (ast->right && (ast->right->token->type == TOKEN_AND_IF ||
						ast->right->token->type == TOKEN_OR_IF))
	{
		if (ast->ret != 0)
			if (read_ast(ast->right->left) == EXIT_SUCCESS)
				ast->ret = ast->right->left->ret;
		if (read_ast(ast->right) == EXIT_SUCCESS)
			ast->ret = ast->right->ret;
	}
	else if (ast->ret != 0)
	{
		if (read_ast(ast->right) == EXIT_SUCCESS)
			ast->ret = ast->right->ret;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Send `char **cmd` to cmd_exec(), and stock process exit status.
**	-------------------------------------------------------------------------- +
*/

static int	ast_cmd(t_ast *ast)
{
	char	**cmd;

	ast->ret = EXIT_SUCCESS;
	if (!(cmd = token_into_array(ast->token)))
		return (EXIT_FAILURE);
	if (cmd_exec_s(cmd, ast->token, &ast->ret) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_arrfree(cmd);
	g_status = ast->ret > 255 ? WEXITSTATUS(ast->ret) : ast->ret;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Read the AST, and executes each command according to the node content.
**	-------------------------------------------------------------------------- +
*/

int			read_ast(t_ast *ast)
{
	if (!ast || !ast->token)
		return (EXIT_SUCCESS);
	else if (ast->token->type == TOKEN_SEMICOLON)
		return (ast_semicolon(ast));
	else if (ast->token->type == TOKEN_AND_IF)
		return (ast_andif(ast));
	else if (ast->token->type == TOKEN_OR_IF)
		return (ast_orif(ast));
	else if (ast->token->type == TOKEN_PIPE)
		return (ast_pipe(ast));
	else if (ast->token->type == TOKEN_WORD)
		return (ast_cmd(ast));
	else
	{
		ft_putstr_fd("42sh: error: read_ast() failed, token: ", STDERR_FILENO);
		ft_putendl_fd(ast->token->content, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}
