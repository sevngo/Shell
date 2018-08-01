#include "../incs/minishell.h"

char		*g_clipboard;

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + v' key combination.
**	-------------------------------------------------------------------------- +
*/

int			kp_paste(t_line **head, char ch, int mode)
{
	char	*str1;
	char	*str2;

	(void)mode;
	if (ch != KP_CTRL_V)
		return (0);
	if (!g_clipboard)
		return (KEY_CTRL_V);
	if ((*head)->line)
	{
		if (!(str1 = ft_strsub((*head)->line, 0, (*head)->cur_pos)))
			return (-1);
		if (!(str2 = ft_strjoin_free(str1, g_clipboard, 1)))
			return (-1);
		if (!(str1 = ft_strsub((*head)->line, (*head)->cur_pos,
				ft_strlen((*head)->line) - (*head)->cur_pos)))
			return (-1);
		ft_strdel(&(*head)->line);
		if (!((*head)->line = ft_strjoin_free(str2, str1, 2)))
			return (-1);
	}
	else if (!((*head)->line = ft_strdup(g_clipboard)))
		return (-1);
	(*head)->cur_pos += ft_strlen(g_clipboard);
	return (KEY_CTRL_V);
}

/*
**	-------------------------------------------------------------------------- +
**	When quitting the main function, remove selection & handles SIGINT.
**	-------------------------------------------------------------------------- +
*/

static int	kp_return(t_line *head, int mode, int prompt_mode)
{
	char	byte[2];

	input_disp(head, -1, KEY_CTRL_D, prompt_mode);
	if (mode == RET_CTRL_C)
	{
		byte[0] = KP_CTRL_C;
		byte[1] = '\0';
		ioctl(STDIN_FILENO, TIOCSTI, byte);
	}
	return (mode == RET_CTRL_C ? KP_CTRL_C : KEY_CTRL_S);
}

/*
**	-------------------------------------------------------------------------- +
**	Removes the selected part from the current line.
**	-------------------------------------------------------------------------- +
*/

static int	kp_cut(t_line **head, char ch, int start)
{
	char	*str1;
	char	*str2;

	if (ch != KP_CTRL_X)
		return (EXIT_SUCCESS);
	if (!(str1 = ft_strsub((*head)->line, 0, start)))
		return (EXIT_FAILURE);
	if (!(str2 = ft_strsub((*head)->line, (*head)->cur_pos,
			ft_strlen((*head)->line) - (*head)->cur_pos)))
		return (EXIT_FAILURE);
	ft_strdel(&(*head)->line);
	if (!((*head)->line = ft_strjoin_free(str1, str2, 2)))
		return (EXIT_FAILURE);
	(*head)->cur_pos = start;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Display the line being selected, inverting color on the selected area.
**	-------------------------------------------------------------------------- +
*/

static void	kp_do_select(t_line *head, int start, int mode)
{
	int	i;

	if (head->cur_pos >= (int)ft_strlen(head->line))
		return ;
	if (*(head->line + head->cur_pos + 1) == '\n')
		mc_right(head);
	mc_right(head);
	input_clear_line(head);
	sh_prompt(mode);
	i = 0;
	while (*(head->line + i))
	{
		if (i == start)
			ft_putstr_fd(C_INVERSE_ON, STDIN_FILENO);
		if (i == head->cur_pos)
			ft_putstr_fd(C_INVERSE_OFF, STDIN_FILENO);
		ft_putchar_fd(*(head->line + i++), STDIN_FILENO);
	}
	input_reset_cursor(head);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles selections ('ctrl + s' key combination), copies, & cuts.
**	-------------------------------------------------------------------------- +
*/

int			kp_select(t_line **head, char ch, int mode)
{
	int		start;

	if (ch != KP_CTRL_S || (*head)->cur_pos == (int)ft_strlen((*head)->line))
		return (0);
	start = (*head)->cur_pos;
	while (ch != '\n' && ch != KP_CTRL_D)
	{
		if (ch == KP_CTRL_S)
			kp_do_select(*head, start, mode);
		else if (ch == KP_CTRL_B || ch == KP_CTRL_X)
		{
			if (g_clipboard)
				ft_strdel(&g_clipboard);
			if (!(g_clipboard = ft_strsub((*head)->line,
				start, (*head)->cur_pos - start)))
				return (-1);
			if (kp_cut(head, ch, start) == EXIT_FAILURE)
				return (-1);
			break ;
		}
		else if (ch == KP_CTRL_C)
			return (kp_return(*head, RET_CTRL_C, mode));
		ch = ft_getch();
	}
	return (kp_return(*head, RET_NEWLINE, mode));
}
