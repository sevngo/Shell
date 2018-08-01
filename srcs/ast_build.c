#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Returns the first greatest control operator (in order,
**	`;' > `&&' > `||' > `|') between two nodes, or NULL if not found.
**	-------------------------------------------------------------------------- +
*/

static t_token	*ast_find_op(t_token *begin, t_token *end)
{
	t_token	*node;
	t_token	*ret;

	ret = begin;
	node = begin;
	while (node != end)
	{
		if (node->type > ret->type && node->type != TOKEN_EOL)
		{
			if (node->type == TOKEN_OR_IF && ret->type == TOKEN_AND_IF)
				;
			else
				ret = node;
		}
		node = node->next;
	}
	if (ret->type == TOKEN_PIPE || ret->type == TOKEN_AND_IF
			|| ret->type == TOKEN_OR_IF || ret->type == TOKEN_SEMICOLON)
		return (ret);
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Creates a new token in the leaf, adding heredoc!
**	-------------------------------------------------------------------------- +
*/

static int		ast_new_token(t_token **head, char *content,
													int type, char ***hd)
{
	t_token	*current;
	t_token	*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (EXIT_FAILURE);
	if (!(new->content = ft_strdup(content)))
		return (EXIT_FAILURE);
	new->type = token_type(content, type);
	if (new->type == TOKEN_DLESS && *hd && **hd && isatty(STDIN_FILENO))
	{
		if (!(new->heredoc = ft_strjoin(**hd, ft_strlen(**hd) > 0 ? "\n" : "")))
			return (EXIT_FAILURE);
		(*hd)++;
	}
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
**	Creates a new leaf in the AST by adding each token between `begin` - `end`,
**	& sets its `left`/`right` value to NULL.
**	-------------------------------------------------------------------------- +
*/

static int		ast_new_leaf(t_ast **leaf, t_token *begin,
										t_token *end, char ***hd)
{
	t_token	*node;

	node = begin;
	while (node != end)
	{
		if (ast_new_token(&(*leaf)->token, node->content,
					node->type, hd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		node = node->next;
	}
	(*leaf)->left = NULL;
	(*leaf)->right = NULL;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Creates a new node in the AST, and call itself again until it created the
**	entire tree.
**	-------------------------------------------------------------------------- +
*/

static t_ast	*ast_new_node(t_ast *root, t_token *begin,
										t_token *end, char ***hd)
{
	t_token	*new_end;
	t_token	*old_end;
	t_ast	*ast;

	old_end = end;
	if (!(ast = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	ast->up = root;
	if ((new_end = ast_find_op(begin, end)) != NULL)
	{
		if (token_add(&ast->token, new_end->content,
				new_end->type) == EXIT_FAILURE)
			return (NULL);
		if (!(ast->left = ast_new_node(ast, begin, new_end, hd)))
			return (NULL);
		if (!(ast->right = ast_new_node(ast, new_end->next, old_end, hd)))
			return (NULL);
	}
	else
	{
		if (ast_new_leaf(&ast, begin, end, hd) == EXIT_FAILURE)
			return (NULL);
	}
	return (ast);
}

/*
**	-------------------------------------------------------------------------- +
**	Calls the function that will build the AST, and returns status.
**	-------------------------------------------------------------------------- +
*/

int				ast_build(t_ast **head, t_token *tokens, char **heredocs)
{
	t_token	*end;
	t_ast	*ast;
	char	**mem;

	ast = NULL;
	end = tokens;
	mem = heredocs;
	while (end->next != NULL)
		end = end->next;
	if (!(ast = ast_new_node(ast, tokens, end, &heredocs)))
		return (EXIT_FAILURE);
	*head = ast;
	heredocs = mem;
	return (EXIT_SUCCESS);
}
