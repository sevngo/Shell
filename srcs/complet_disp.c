#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	print the list of possibility or the complet word if there is only one
**	-------------------------------------------------------------------------- +
*/

int			print_many(t_complet *comp)
{
	int				i;
	int				nb_per_line;
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0)
		return (0);
	nb_per_line = ws.ws_col / (comp->len_max + 2);
	i = 0;
	ft_putchar('\n');
	while (comp->list)
	{
		if (i >= nb_per_line)
		{
			i = 0;
			ft_putchar('\n');
		}
		ft_putstr(comp->list->name);
		ft_putchar_nb_fd(1, ' ', comp->len_max - ft_strlen(comp->list->name) +
																			2);
		comp->list = comp->list->next;
		i++;
	}
	ft_putchar('\n');
	return (0);
}

char		*print_one(t_complet *comp, char *input)
{
	char	*tmp;
	int		i;

	tmp = input;
	i = 0;
	while (input[i])
		i++;
	while (!(ft_isspace(input[i])) && i > 0)
		i--;
	i = (i > 0) ? i + 1 : i;
	input[i] = '\0';
	if (comp->path && comp->path[0])
	{
		if (!(input =
					ft_strjoin_separator(tmp, comp->list->name, comp->path, 0)))
			return (NULL);
	}
	else
	{
		if (!(input = ft_strjoin(tmp, comp->list->name)))
			return (NULL);
	}
	ft_free(tmp);
	return (input);
}

char		*print_words(t_complet *comp, char *input)
{
	char			*tmp;
	t_list_words	*begin;

	begin = comp->list;
	if (comp->list->next == NULL)
	{
		if (!(tmp = print_one(comp, input)))
		{
			comp->list = begin;
			return (input);
		}
		else
		{
			comp->list = begin;
			return (tmp);
		}
	}
	else
		print_many(comp);
	comp->list = begin;
	return (input);
}
