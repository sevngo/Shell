#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Move the cursor left, or in an appropriate manner if cursor is at the edge.
**	-------------------------------------------------------------------------- +
*/

static void	handle_prompt(int pos)
{
	if (pos != 0)
		return ;
	pos = 3;
	while (pos-- > 0)
		tputs(tgetstr("nd", NULL), 1, &tc_putc);
}

void		mc_left(t_line *head)
{
	int	rows;
	int	cols;
	int	i;

	if (head->cur_pos < 1 || get_window_size(&rows, &cols) == EXIT_FAILURE)
		return ;
	if (head->line[head->cur_pos - 1] == '\n')
	{
		tputs(tgetstr("up", NULL), 1, &tc_putc);
		i = head->cur_pos - 1;
		while (i > 0 && head->line[i-- - 1] != '\n')
			tputs(tgetstr("nd", NULL), 1, &tc_putc);
		handle_prompt(i);
	}
	else
		tputs(tgetstr("le", NULL), 1, &tc_putc);
	head->cur_pos--;
}

/*
**	-------------------------------------------------------------------------- +
**	Move the cursor right, or in an appropriate manner if cursor is at the edge.
**	-------------------------------------------------------------------------- +
*/

void		mc_right(t_line *head)
{
	int	rows;
	int	cols;

	if (head->cur_pos > (int)ft_strlen(head->line))
		return ;
	if (get_window_size(&rows, &cols) == EXIT_FAILURE)
		return ;
	if (head->line[head->cur_pos] == '\n'
			|| ((head->cur_pos + 1) + 3) % cols == 0)
	{
		tputs(tgetstr("do", NULL), 1, &tc_putc);
		tputs(tgetstr("cr", NULL), 1, &tc_putc);
	}
	else
		tputs(tgetstr("nd", NULL), 1, &tc_putc);
	head->cur_pos++;
}
