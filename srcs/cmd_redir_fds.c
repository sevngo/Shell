#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Adds a new node containing file descriptors to the linked list.
**
**	Return values:
**	-1				- error (such as malloc()), program should be exited
**	EXIT_SUCCESS	- everything went fine, command should be executed
**	-------------------------------------------------------------------------- +
*/

int		cmd_redir_fds_add(t_redir **head, int fd_old, int fd_save)
{
	t_redir	*node;
	t_redir	*new;

	if (!(new = ft_memalloc(sizeof(t_redir))))
		return (-1);
	new->old = fd_old;
	new->save = fd_save;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Reverses the linked list so the file descriptors are restored in the
**	right order.
**	-------------------------------------------------------------------------- +
*/

void	cmd_redir_fds_rev(t_redir **head)
{
	t_redir	*middle;
	t_redir	*front;
	t_redir	*back;

	if (*head)
	{
		middle = *head;
		front = middle->next;
		back = NULL;
		while (1)
		{
			middle->next = back;
			if (!front)
				break ;
			back = middle;
			middle = front;
			front = front->next;
		}
		*head = middle;
	}
}
