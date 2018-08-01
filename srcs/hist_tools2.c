#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Checks if given entry already exists in history list.
**	-------------------------------------------------------------------------- +
*/

int		hist_exists(char *new_entry)
{
	t_hist	*node;

	node = g_hist;
	while (node)
	{
		if (ft_strcmp(node->line, new_entry) == 0)
			return (TRUE);
		node = node->next;
	}
	return (FALSE);
}

/*
**	-------------------------------------------------------------------------- +
**	Return the size of the current history list.
**	-------------------------------------------------------------------------- +
*/

int		hist_write(char *spec_file, int open_mode)
{
	t_hist	*node;
	char	*histfile;
	int		fd;

	if (spec_file)
		histfile = spec_file;
	else if ((histfile = env_get_val("HISTFILE"))
			&& ft_strisblank(histfile) == FALSE)
		;
	else
		histfile = HISTFILE;
	if ((fd = open(histfile, (O_CREAT | open_mode | O_WRONLY), 0600)) == -1)
		return (sh_return("can't open history file"));
	node = g_hist;
	while (node)
	{
		ft_putendl_fd(node->line, fd);
		node = node->next;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Return the size of the current history list.
**	-------------------------------------------------------------------------- +
*/

int		hist_size(void)
{
	t_hist	*node;
	int		len;

	len = 0;
	node = g_hist;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

/*
**	-------------------------------------------------------------------------- +
**	Remove given `node` from history list.
**	-------------------------------------------------------------------------- +
*/

void	hist_del_node(t_hist **head, t_hist *node)
{
	t_hist	*prev;
	t_hist	*curr;
	t_hist	*tmp;

	if (node == *head)
	{
		tmp = *head;
		*head = (*head)->next;
	}
	prev = *head ? *head : NULL;
	curr = *head ? (*head)->next : NULL;
	while (prev && curr)
	{
		if (node == curr)
		{
			tmp = curr;
			prev->next = curr->next;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	ft_strdel(&tmp->line);
	ft_free(tmp);
}
