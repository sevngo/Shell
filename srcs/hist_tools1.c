#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Sets all node "current" status to FALSE.
**	-------------------------------------------------------------------------- +
*/

void		hist_init(t_hist **head)
{
	t_hist	*node;

	node = *head;
	while (node)
	{
		node->current = FALSE;
		node = node->next;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the last node of the command history linked list, or the node
**	preceding the node with "current "status TRUE.
**	-------------------------------------------------------------------------- +
*/

t_hist		*hist_getpoc(t_hist **head)
{
	t_hist	*node;

	if (!*head)
		return (NULL);
	if ((*head)->current == TRUE)
		return (*head);
	node = *head;
	while (node->next)
	{
		if (node->next->current == TRUE)
		{
			node->next->current = FALSE;
			break ;
		}
		node = node->next;
	}
	node->current = TRUE;
	return (node);
}

/*
**	-------------------------------------------------------------------------- +
**	Returns the node right after the one with "current" status TRUE.
**	-------------------------------------------------------------------------- +
*/

t_hist		*hist_getnoc(t_hist **head)
{
	t_hist	*node;

	if (!*head)
		return (NULL);
	node = *head;
	while (node->next)
	{
		if (node->current == TRUE)
		{
			node->current = FALSE;
			node = node->next;
			node->current = TRUE;
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/*
**	-------------------------------------------------------------------------- +
**	Appends new command (& related data) to the command history linked list.
**	-------------------------------------------------------------------------- +
*/

static int	hist_exists_last(t_hist **head, char *input)
{
	t_hist	*node;

	if (!*head)
		return (FALSE);
	node = *head;
	while (node->next)
		node = node->next;
	if (ft_strcmp(node->line, input) == 0)
		return (TRUE);
	return (FALSE);
}

int			hist_append(t_hist **head, char *input)
{
	t_hist	*current;
	t_hist	*new;

	if (ft_strisblank(input) == TRUE || hist_exists_last(head, input) == TRUE)
		return (EXIT_SUCCESS);
	if (!(new = ft_memalloc(sizeof(t_hist))))
		return (EXIT_FAILURE);
	if (!(new->line = ft_strdup(input)))
		return (EXIT_FAILURE);
	new->current = FALSE;
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
