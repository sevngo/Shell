#include "../incs/minishell.h"

/*
** https://www.gnu.org/software/bash/manual/html_node/Bash-History-Builtins.html
** https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html
*/

/*
**	-------------------------------------------------------------------------- +
**	history -ps arg [arg ...]
**	-p	Perform history substitution on the `args` and display the result on
**		the standard output, without storing the results in the history list.
**	Note: the -p option to the history builtin command may be used to see what
**	a history expansion will do before using it.
**
**	-s	Perform history substitution on the `args` and add them to the end of
**		the history list as a single entry.
**	Note: the -s option to the history builtin may be used to add commands to
**	the end of the history list without actually executing them, so that they
**	are available for subsequent recall.
**	-------------------------------------------------------------------------- +
*/

int			hist_optp(char **args)
{
	t_hist	*node;
	int		i;

	i = 2;
	node = g_hist;
	while (node->next)
		node = node->next;
	hist_del_node(&g_hist, node);
	while (args[i])
	{
		ft_putendl_fd(args[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}

int			hist_opts(char **args)
{
	t_hist	*node;
	char	*entry;
	char	*tmp;
	int		i;

	i = 2;
	node = g_hist;
	while (node->next)
		node = node->next;
	hist_del_node(&g_hist, node);
	if (!(entry = ft_strjoin(args[i++], " ")))
		return (EXIT_FAILURE);
	while (args[i])
	{
		if (!(tmp = ft_strjoin_free(entry, args[i], 1)))
			return (EXIT_FAILURE);
		if (!(entry = ft_strjoin_free(tmp, args[i + 1] ? " " : "", 1)))
			return (EXIT_FAILURE);
		i++;
	}
	hist_append(&g_hist, entry);
	ft_strdel(&entry);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	history -d offset
**	Delete the history entry at position `offset`.
**	-------------------------------------------------------------------------- +
*/

static int	hist_optd_err(char **args)
{
	int	size;

	size = hist_size();
	if (!args[2])
	{
		ft_putstr_fd("42sh: history: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": option requires an argument", STDERR_FILENO);
		return (2);
	}
	else if (size == 1 || (args[2] && (ft_strisdigit(args[2]) == FALSE ||
				ft_atoi(args[2]) >= size)))
	{
		ft_putstr_fd("42sh: history: ", STDERR_FILENO);
		ft_putstr_fd(args[2], STDERR_FILENO);
		ft_putendl_fd(": history position out of range", STDERR_FILENO);
		return (2);
	}
	return (EXIT_SUCCESS);
}

int			hist_optd(char **args)
{
	t_hist	*node;
	int		i;

	if (hist_optd_err(args) == 2)
		return (2);
	i = 0;
	node = g_hist;
	while (node)
	{
		if (i == ft_atoi(args[2]))
		{
			hist_del_node(&g_hist, node);
			break ;
		}
		node = node->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	history -c
**	Clear the history list by deleting all the entries.
**	-------------------------------------------------------------------------- +
*/

int			hist_optc(void)
{
	free_hist(&g_hist);
	g_hist = NULL;
	return (EXIT_SUCCESS);
}
