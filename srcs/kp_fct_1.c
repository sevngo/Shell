#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'backspace' key.
**	-------------------------------------------------------------------------- +
*/

int			kp_backspace(t_line **head, char ch, int mode)
{
	int	index;

	(void)mode;
	if (ch != KP_BACKSPACE || (*head)->cur_pos < 1)
		return (0);
	if (ft_strlen((*head)->line) == 0)
		return (KEY_BACKSPACE);
	input_clear_line(*head);
	index = (*head)->cur_pos - 1;
	ft_memmove(&(*head)->line[index], &(*head)->line[index + 1],
			ft_strlen((*head)->line) - index);
	(*head)->cur_pos--;
	return (KEY_BACKSPACE);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + d' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_d(t_line **head, char ch, int mode)
{
	extern char	**environ;
	char		byte[2];

	if (ch != KP_CTRL_D)
		return (0);
	if (ft_strchr((*head)->line, '\n'))
		return (KEY_CTRL_D);
	if ((*head)->cur_pos == 0 && ft_strlen((*head)->line) == 0)
	{
		if (mode == PROMPT_BASIC)
			my_exit(NULL, &mode);
		byte[0] = KP_CTRL_D2;
		byte[1] = '\0';
		ioctl(STDIN_FILENO, TIOCSTI, byte);
		return (KP_CTRL_D2);
	}
	else if ((*head)->cur_pos >= (int)ft_strlen((*head)->line))
		return (KEY_CTRL_D);
	(*head)->cur_pos++;
	kp_backspace(head, KP_BACKSPACE, mode);
	return (KEY_CTRL_D);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + l' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_ctrl_l(t_line **head, char ch, int mode)
{
	(void)head;
	(void)mode;
	if (ch != KP_CTRL_L)
		return (0);
	tputs(tgetstr("cl", NULL), 1, &tc_putc);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, &tc_putc);
	return (KEY_CTRL_L);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles escape sequences key combination containing 'option' key.
**	-------------------------------------------------------------------------- +
*/

static int	kp_esc_seq_opt(t_line **head, char ch)
{
	static int	(*kp_fct[])(t_line **, char) = {
	&kp_opt_down_arrow,
	&kp_opt_left_arrow,
	&kp_opt_right_arrow,
	&kp_opt_up_arrow,
	NULL};
	int			ret;
	int			i;

	if (ch != KP_ESC)
		return (0);
	i = 0;
	ch = ft_getch();
	ch = ft_getch();
	while (kp_fct[i] && (ret = kp_fct[i](head, ch)) == 0)
		i++;
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles escape sequences keys combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_esc_seq(t_line **head, char ch, int mode)
{
	static int	(*kp_fct[])(t_line **, char) = {
	&kp_end,
	&kp_home,
	&kp_down_arrow,
	&kp_up_arrow,
	&kp_left_arrow,
	&kp_right_arrow,
	NULL};
	int			ret;
	int			i;

	(void)mode;
	if (ch != KP_ESC)
		return (0);
	i = 0;
	ch = ft_getch();
	if (ch == CH_SQUARE_BRACKET)
	{
		ch = ft_getch();
		while (kp_fct[i] && (ret = kp_fct[i](head, ch)) == 0)
			i++;
		return (ret);
	}
	return (kp_esc_seq_opt(head, ch));
}
