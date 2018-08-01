#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Move cursor back to where it was before erasing the line.
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

void		input_reset_cursor(t_line *head)
{
	int	rows;
	int	cols;
	int	moves;
	int	pos;
	int	i;

	if (get_window_size(&rows, &cols) == EXIT_FAILURE)
		return ;
	pos = ft_strlen(head->line);
	moves = pos - head->cur_pos;
	while (moves > 0)
	{
		if (head->line[pos - 1] == '\n')
		{
			tputs(tgetstr("up", NULL), 1, &tc_putc);
			i = pos - 1;
			while (i > 0 && head->line[i-- - 1] != '\n')
				tputs(tgetstr("nd", NULL), 1, &tc_putc);
			handle_prompt(i);
		}
		else
			tputs(tgetstr("le", NULL), 1, &tc_putc);
		moves--;
		pos--;
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Move cursor to the beginning of the current input string, and clear the
**	screen from current cursor position to bottom screen.
**	-------------------------------------------------------------------------- +
*/

void		input_clear_line(t_line *head)
{
	int	i;

	i = head->cur_pos;
	if (ft_strchr(head->line, '\n'))
	{
		while (i > -1)
		{
			if (head->line[i--] == '\n')
				tputs(tgetstr("up", NULL), 1, &tc_putc);
			else
				tputs(tgetstr("le", NULL), 1, &tc_putc);
		}
	}
	else
		while (i-- > 0)
			tputs(tgetstr("le", NULL), 1, &tc_putc);
	tputs(tgetstr("cr", NULL), 1, &tc_putc);
	tputs(tgetstr("cd", NULL), 1, &tc_putc);
}

/*
**	-------------------------------------------------------------------------- +
**	Handle the display of the current input.
**	-------------------------------------------------------------------------- +
*/

void		input_disp(t_line *head, char ch, int key, int mode)
{
	if (ch >= 32 && ch <= 126 && head->cur_pos == (int)ft_strlen(head->line))
		ft_putchar_fd(ch, STDIN_FILENO);
	else if ((ch >= 32 && ch <= 126) || key == KEY_CTRL_L || key == KEY_CTRL_D
			|| key == KEY_DOWN_ARROW || key == KEY_UP_ARROW || key == KEY_CTRL_V
			|| key == KEY_BACKSPACE || key == KEY_TAB)
	{
		if ((ch >= 32 && ch <= 126) || key == KEY_CTRL_D || key == KEY_CTRL_V
				|| key == KEY_TAB)
			input_clear_line(head);
		sh_prompt(mode);
		ft_putstr_fd(head->line, STDIN_FILENO);
		input_reset_cursor(head);
	}
}
