#include "../incs/minishell.h"

/*
** https://www.gnu.org/software/bash/manual/html_node/Bash-History-Builtins.html
** https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html
*/

/*
**	-------------------------------------------------------------------------- +
**	history [n]
**	With no options, display the command history list with line numbers.
**	An argument of `n` lists only the last `n` lines.
**	-------------------------------------------------------------------------- +
*/

static int	hist_nopt_err(char **args)
{
	if (args[1] && ft_strisdigit(args[1]) == FALSE)
	{
		ft_putstr_fd("42sh: history: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (args[1] && args[2])
	{
		ft_putendl_fd("42sh: history: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	hist_nopt(char **args)
{
	t_hist	*node;
	int		size;
	int		i;
	int		j;

	if (hist_nopt_err(args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	node = g_hist;
	size = hist_size();
	while (node && i < size)
	{
		if (!args[1] || (args[1] && i >= (size - ft_atoi(args[1]))))
		{
			j = -1;
			while (j++ < (int)(ft_intlen(size) - ft_intlen(i)))
				ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putnbr_fd(i, STDOUT_FILENO);
			ft_putstr_fd("  ", STDOUT_FILENO);
			ft_putendl_fd(node->line, STDOUT_FILENO);
		}
		node = node->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	history [n]
**	history -c
**	history -d
**	history -awrn [filename]
**	history -ps arg [arg ...]
**
**	Return -1, EXIT_SUCCESS or EXIT_FAILURE only.
**	-------------------------------------------------------------------------- +
*/

static int	hist_usage(char **args)
{
	ft_putstr_fd("42sh: history: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("history: usage: history [n] [-c] [-d offset]",
			STDERR_FILENO);
	ft_putendl_fd("                history -awrn [filename]", STDERR_FILENO);
	ft_putendl_fd("                history -ps arg [arg ...]", STDERR_FILENO);
	return (2);
}

int			my_history(char **args, int *status)
{
	if (args[1] && *args[1] == '-')
	{
		if (ft_strcmp(args[1], "-c") == 0)
			*status = hist_optc();
		else if (ft_strcmp(args[1], "-d") == 0)
			*status = hist_optd(args);
		else if (ft_strcmp(args[1], "-a") == 0)
			*status = hist_opta(args);
		else if (ft_strcmp(args[1], "-w") == 0)
			*status = hist_optw(args);
		else if (ft_strcmp(args[1], "-r") == 0)
			*status = hist_optr(args);
		else if (ft_strcmp(args[1], "-n") == 0)
			*status = hist_optn(args);
		else if (ft_strcmp(args[1], "-p") == 0)
			*status = hist_optp(args);
		else if (ft_strcmp(args[1], "-s") == 0)
			*status = hist_opts(args);
		else
			*status = hist_usage(args);
	}
	else
		*status = hist_nopt(args);
	return (*status == -1 ? -1 : EXIT_SUCCESS);
}
