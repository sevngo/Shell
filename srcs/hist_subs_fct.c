#include "../incs/minishell.h"

/*
** https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html
** https://www.gnu.org/software/bash/manual/html_node/Event-Designators.html
*/

/*
**	-------------------------------------------------------------------------- +
**	Display "event not found" message & avoid adding new entry in history list.
**	Returns 2 (!= EXIT_SUCCESS) on success so the loop breaks on the first err.
**	-------------------------------------------------------------------------- +
*/

int	hist_err(char **input, char *arg)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": event not found", STDERR_FILENO);
	ft_strdel(&arg);
	ft_strdel(&input[0]);
	return (!(input[0] = ft_strnew(0)) ? EXIT_FAILURE : 2);
}

/*
**	-------------------------------------------------------------------------- +
**	!string
**	Refer to the most recent command in the history list starting with `string`.
**	-------------------------------------------------------------------------- +
*/

int	hist_str(char **input, char *arg, int arg_size)
{
	t_hist	*node;
	char	*new_args;
	char	*match;

	match = NULL;
	node = g_hist;
	while (node)
	{
		if (ft_strncmp(arg + 1, node->line, ft_strlen(arg + 1)) == 0)
		{
			match ? ft_strdel(&match) : 0;
			if (!(match = ft_strdup(node->line)))
				return (EXIT_FAILURE);
		}
		node = node->next;
	}
	if (!match)
		return (hist_err(input, arg));
	ft_strdel(&arg);
	if (!(new_args = ft_strsub(*input, arg_size, ft_strlen(*input) - arg_size)))
		return (EXIT_FAILURE);
	ft_strdel(&*input);
	if (!(*input = ft_strjoin_free(match, new_args, 2)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	!-n
**	Refer to the command `n` lines back in the history list.
**	!!
**	Refer to the previous command in history list. This is a synonym for `!-1`.
**	-------------------------------------------------------------------------- +
*/

int	hist_mth(char **input, char *arg, int arg_size, int mode)
{
	t_hist	*node;
	char	*new_args;
	int		size;
	int		i;

	i = 0;
	if ((size = hist_size()) == 0 ||
		(ft_atoi(arg + 2) == 0 && ft_strcmp(arg, "!!") != 0) ||
		(mode == BANG_MINUS && ft_atoi(arg + 2) > size))
		return (hist_err(input, arg));
	node = g_hist;
	while (node->next && i++ < (size - ft_atoi(arg + 2)))
		node = node->next;
	ft_strdel(&arg);
	if (!(new_args = ft_strsub(*input, arg_size, ft_strlen(*input) - arg_size)))
		return (EXIT_FAILURE);
	ft_strdel(&*input);
	if (!(*input = ft_strjoin(node->line, new_args)))
		return (EXIT_FAILURE);
	ft_strdel(&new_args);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	!n
**	Refer to command line `n` in the history list.
**	-------------------------------------------------------------------------- +
*/

int	hist_nth(char **input, char *arg, int arg_size)
{
	t_hist	*node;
	char	*new_args;
	int		size;
	int		i;

	i = 0;
	if ((size = hist_size()) == 0 || ft_atoi(arg + 1) >= size)
		return (hist_err(input, arg));
	node = g_hist;
	while (node->next && i < size && i++ < ft_atoi(arg + 1))
		node = node->next;
	ft_strdel(&arg);
	if (!(new_args = ft_strsub(*input, arg_size, ft_strlen(*input) - arg_size)))
		return (EXIT_FAILURE);
	ft_strdel(&*input);
	if (!(*input = ft_strjoin(node->line, new_args)))
		return (EXIT_FAILURE);
	ft_strdel(&new_args);
	return (EXIT_SUCCESS);
}
