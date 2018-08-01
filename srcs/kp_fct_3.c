#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	If the history start being browsed as the current line is not empty, save it
**	and restore it when neeeded with following function.
**	-------------------------------------------------------------------------- +
*/

int	save_curr_line(t_line **head, int mode, char **str)
{
	static char	*line = NULL;
	t_hist		*node;

	if (mode == LINE_SAVE)
	{
		node = g_hist;
		while (node)
		{
			if (node->current == TRUE)
				return (EXIT_SUCCESS);
			node = node->next;
		}
		ft_strdel(&line);
		if (!(line = ft_strdup((*head)->line ? (*head)->line : "")))
			return (EXIT_FAILURE);
	}
	else if (mode == LINE_GIVE)
	{
		if (str)
			if (!(*str = ft_strdup(line ? line : "")))
				return (EXIT_FAILURE);
	}
	else if (mode == LINE_FREE)
		ft_strdel(&line);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'down arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_down_arrow(t_line **head, char ch)
{
	t_hist	*node;

	if (ch != CH_DOWN)
		return (0);
	input_clear_line(*head);
	if (!(node = hist_getnoc(&g_hist)))
	{
		if (!g_hist)
			return (KEY_DOWN_ARROW);
		ft_strdel(&(*head)->line);
		if (save_curr_line(head, LINE_GIVE, &(*head)->line) == EXIT_FAILURE)
			return (-1);
		(*head)->cur_pos = ft_strlen((*head)->line);
		hist_init(&g_hist);
	}
	else
	{
		ft_strdel(&(*head)->line);
		if (!((*head)->line = ft_strdup(node->line)))
			return (-1);
		(*head)->cur_pos = ft_strlen((*head)->line);
	}
	return (KEY_DOWN_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'up arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_up_arrow(t_line **head, char ch)
{
	t_hist	*node;

	if (ch != CH_UP)
		return (0);
	if (save_curr_line(head, LINE_SAVE, NULL) == EXIT_FAILURE)
		return (-1);
	input_clear_line(*head);
	if (!(node = hist_getpoc(&g_hist)))
		return (KEY_UP_ARROW);
	ft_strdel(&(*head)->line);
	if (!((*head)->line = ft_strdup(node->line)))
		return (-1);
	(*head)->cur_pos = ft_strlen((*head)->line);
	return (KEY_UP_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'left arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_left_arrow(t_line **head, char ch)
{
	if (ch != CH_LEFT)
		return (0);
	if ((*head)->cur_pos > 0)
		mc_left(*head);
	return (KEY_LEFT_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'right arrow' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_right_arrow(t_line **head, char ch)
{
	if (ch != CH_RIGHT)
		return (0);
	if ((*head)->cur_pos < (int)ft_strlen((*head)->line))
		mc_right(*head);
	return (KEY_RIGHT_ARROW);
}
