#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Releases the memory of the tokens.
**	-------------------------------------------------------------------------- +
*/

void		free_token(t_token **head)
{
	t_token	*node;
	t_token	*mem;

	node = *head;
	while (node)
	{
		ft_strdel(&node->content);
		if (node->heredoc)
			ft_strdel(&node->heredoc);
		mem = node->next;
		ft_free(node);
		node = mem;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Releases the memory of the AST.
**	-------------------------------------------------------------------------- +
*/

void		free_ast(t_ast **head)
{
	t_ast	*mem;

	free_token(&(*head)->token);
	mem = *head;
	if ((*head)->left)
		free_ast(&(*head)->left);
	if ((*head)->right)
		free_ast(&(*head)->right);
	ft_free(mem);
}

/*
**	-------------------------------------------------------------------------- +
**	Releases the memory of the history.
**	-------------------------------------------------------------------------- +
*/

void		free_hist(t_hist **head)
{
	t_hist	*node;
	t_hist	*mem;

	node = *head;
	while (node)
	{
		mem = node->next;
		ft_strdel(&node->line);
		ft_free(node);
		node = mem;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Adds 1 to the SHLVL entry in the environ, or create one if nonexistent.
**	-------------------------------------------------------------------------- +
*/

static int	env_shlvl_up(void)
{
	char	*string_lvl;
	int		nb_lvl;

	if ((string_lvl = env_get_val("SHLVL")) != NULL)
	{
		nb_lvl = ft_atoi(string_lvl);
		nb_lvl++;
		if (!(string_lvl = ft_itoa(nb_lvl)))
			return (sh_return("malloc(3) failed"));
		if (env_replace("SHLVL", string_lvl) == EXIT_FAILURE)
			return (sh_return("malloc(3) failed"));
		ft_strdel(&string_lvl);
	}
	else
	{
		if (env_append("SHLVL", "1") == EXIT_FAILURE)
			return (sh_return("malloc(3) failed"));
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Copies the whole environment, and increases SHLVL by one.
**	Also, if the original environ does not contain SHLVL, TERM, PWD and PATH
**	entries, it will add them with default values.
**	-------------------------------------------------------------------------- +
*/

int			env_init(void)
{
	extern char	**environ;
	char		*hist_path;

	if (!(environ = ft_arrdup(environ)))
		return (sh_return("malloc(3) failed"));
	if (env_shlvl_up() == EXIT_FAILURE)
		return (sh_return("malloc(3) failed"));
	if (!env_get_val("TERM"))
		if (env_append("TERM", "xterm-256color") == EXIT_FAILURE)
			return (sh_return("malloc(3) failed"));
	if (!env_get_val("PATH"))
		if (env_append("PATH", "/bin:/usr/bin") == EXIT_FAILURE)
			return (sh_return("malloc(3) failed"));
	if (!env_get_val("HISTFILE"))
	{
		if (!(hist_path = get_hist_path()))
			return (sh_return("malloc(3) failed"));
		if (env_append("HISTFILE", hist_path) == EXIT_FAILURE)
			return (sh_return("malloc(3) failed"));
		ft_strdel(&hist_path);
	}
	return (EXIT_SUCCESS);
}
