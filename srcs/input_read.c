#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'ctrl + c' & 'ctrl + d' key combinations.
**	-------------------------------------------------------------------------- +
*/

static int	input_ctrl(t_line **head, char **input, char ch, int mode)
{
	kp_end(head, CH_END);
	if (ch == KP_CTRL_C)
		ft_putendl_fd("^C", STDIN_FILENO);
	else if (ch == KP_CTRL_D2 && mode == PROMPT_HDOCS)
		ft_putendl_fd("^D", STDIN_FILENO);
	else if (ch == KP_CTRL_D2 && mode == PROMPT_QUOTE)
		ft_putendl_fd("42sh: syntax error: unexpected EOF", STDERR_FILENO);
	ft_strdel(&(*head)->line);
	ft_free(*head);
	if (!(*input = ft_strnew(0)))
		return (EXIT_FAILURE);
	if (def_term_mode(TERM_RESET) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ch == KP_CTRL_D2 && mode == PROMPT_HDOCS)
		return (EXIT_CTRL_D);
	return (EXIT_CTRL_C);
}

/*
**	-------------------------------------------------------------------------- +
**	Called if the character is not displayable, it calls the function
**	associated with the key press (might be a key combination).
**	-------------------------------------------------------------------------- +
*/

static int	input_keypress(t_line **head, char ch, int mode)
{
	static int	(*kp_fct[])(t_line **, char, int) = {
	&kp_backspace,
	&kp_ctrl_d,
	&kp_ctrl_l,
	&kp_esc_seq,
	&kp_ctrl_e,
	&kp_ctrl_a,
	&kp_select,
	&kp_paste,
	&kp_tab,
	NULL};
	int			ret;
	int			i;

	i = 0;
	while (kp_fct[i] && (ret = kp_fct[i](head, ch, mode)) == 0)
		i++;
	return (ret);
}

/*
**	-------------------------------------------------------------------------- +
**	Insert given character in the input string, at the current cursor position.
**	-------------------------------------------------------------------------- +
*/

static int	input_insert(t_line *head, char ch)
{
	char	*str1;
	char	*str2;

	if (!(str1 = ft_strsub(head->line, 0, head->cur_pos + 1)))
		return (EXIT_FAILURE);
	*(str1 + head->cur_pos) = ch;
	if (!(str2 = ft_strsub(head->line, head->cur_pos,
			ft_strlen(head->line) - head->cur_pos)))
		return (EXIT_FAILURE);
	ft_strdel(&head->line);
	if (!(head->line = ft_strjoin_free(str1, str2, 2)))
		return (EXIT_FAILURE);
	head->cur_pos++;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	When starting the line edition, it turn raw term mode on, and initializes
**	the structure.
**	Once the line has been edited, it turn raw term mode off, and releases the
**	memory allocated during the line edition.
**	-------------------------------------------------------------------------- +
*/

static int	input_tools(t_line **head, char *input, int mode)
{
	if (mode == INPUT_INIT)
	{
		if (!(*head = ft_memalloc(sizeof(t_line))))
			return (EXIT_FAILURE);
		if (!((*head)->line = (input ? ft_strdup(input) : ft_strnew(0))))
			return (EXIT_FAILURE);
		(*head)->cur_pos = 0;
		if (raw_term_mode() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (mode == INPUT_RESET)
	{
		ft_strdel(&(*head)->line);
		ft_free(*head);
		if (def_term_mode(TERM_RESET) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Read what the user types, one byte at a time, and create a string out of it
**	by concatenating them. It stops when the current byte is a newline (`\n').
**	It also call accurate functions on special key presses (arrow keys, etc.).
**	-------------------------------------------------------------------------- +
*/

int			input_read(char **input, int mode)
{
	t_line	*head;
	char	ch;
	int		key;

	if (input_tools(&head, *input, INPUT_INIT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while ((ch = ft_getch()) && ch != '\n')
	{
		if (ch >= 32 && ch <= 126)
		{
			if (input_insert(head, ch) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ch == KP_CTRL_C || ch == KP_CTRL_D2)
			return (input_ctrl(&head, input, ch, mode));
		else if ((key = input_keypress(&head, ch, mode)) == -1)
			return (EXIT_FAILURE);
		input_disp(head, ch, key, mode);
	}
	kp_end(&head, CH_END);
	ft_putchar_fd('\n', STDIN_FILENO);
	if (!(*input = ft_strdup(head->line)))
		return (EXIT_FAILURE);
	return (input_tools(&head, *input, INPUT_RESET));
}
