#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + down arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_opt_down_arrow(t_line **head, char ch)
{
	int	rows;
	int	cols;
	int	i;

	if (ch != CH_DOWN)
		return (0);
	if (ft_strchr((*head)->line, '\n'))
		return (KEY_O_DOWN_ARROW);
	if (get_window_size(&rows, &cols) == EXIT_FAILURE)
		return (KEY_O_DOWN_ARROW);
	if ((*head)->cur_pos < ((int)ft_strlen((*head)->line) - cols))
	{
		i = 0;
		while (i++ < cols)
			mc_right(*head);
	}
	return (KEY_O_DOWN_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + up arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_opt_up_arrow(t_line **head, char ch)
{
	int	rows;
	int	cols;
	int	i;

	if (ch != CH_UP)
		return (0);
	if (ft_strchr((*head)->line, '\n'))
		return (KEY_O_DOWN_ARROW);
	if (get_window_size(&rows, &cols) == EXIT_FAILURE)
		return (KEY_O_UP_ARROW);
	if ((*head)->cur_pos >= cols)
	{
		i = 0;
		while (i++ < cols)
			mc_left(*head);
	}
	return (KEY_O_UP_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + left arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_opt_left_arrow(t_line **head, char ch)
{
	int	i;

	if (ch != CH_LEFT)
		return (0);
	if (ft_strchr((*head)->line, '\n'))
		return (KEY_O_DOWN_ARROW);
	if ((*head)->cur_pos < 1)
		return (KEY_O_LEFT_ARROW);
	i = (*head)->cur_pos;
	while (i > 0 && (*head)->line[i - 1] == ' ')
	{
		mc_left(*head);
		i--;
	}
	while (i > 0 && (*head)->line[i - 1] != ' ')
	{
		mc_left(*head);
		i--;
	}
	return (KEY_O_LEFT_ARROW);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'option + right arrow' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_opt_right_arrow(t_line **head, char ch)
{
	int	i;

	if (ch != CH_RIGHT)
		return (0);
	if (ft_strchr((*head)->line, '\n'))
		return (KEY_O_DOWN_ARROW);
	if ((*head)->cur_pos >= (int)ft_strlen((*head)->line))
		return (KEY_O_RIGHT_ARROW);
	i = (*head)->cur_pos;
	while (i < (int)ft_strlen((*head)->line) && (*head)->line[i + 1] != ' ')
	{
		mc_right(*head);
		i++;
	}
	while (i < (int)ft_strlen((*head)->line) && (*head)->line[i + 1] == ' ')
	{
		mc_right(*head);
		i++;
	}
	if ((*head)->cur_pos < (int)ft_strlen((*head)->line))
		mc_right(*head);
	return (KEY_O_RIGHT_ARROW);
}
