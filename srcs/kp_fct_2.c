#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Handles 'tab' key.
**	-------------------------------------------------------------------------- +
*/

int	kp_tab(t_line **head, char ch, int mode)
{
	char	*tmp;
	char	*tmp2;

	(void)mode;
	if (ch != CH_TAB)
		return (0);
	(void)head;
	if (!(tmp = ft_strsub((*head)->line, 0, (*head)->cur_pos)))
		return (-1);
	if (!(tmp = completion(tmp)))
		return (-1);
	if (!(tmp2 = ft_strsub((*head)->line, (*head)->cur_pos,
				ft_strlen(&((*head)->line[(*head)->cur_pos])))))
		return (-1);
	ft_free((*head)->line);
	if (!((*head)->line = ft_strjoin(tmp, tmp2)))
		return (-1);
	(*head)->cur_pos = ft_strlen(tmp);
	ft_free(tmp);
	ft_free(tmp2);
	return (KEY_TAB);
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'end' key, and 'ctrl + e' key combination (alias for 'end').
**	-------------------------------------------------------------------------- +
*/

int	kp_end(t_line **head, char ch)
{
	if (ch != CH_END)
		return (0);
	while ((*head)->cur_pos < (int)ft_strlen((*head)->line))
		mc_right(*head);
	return (KEY_END);
}

int	kp_ctrl_e(t_line **head, char ch, int mode)
{
	(void)mode;
	if (ch != KP_CTRL_E)
		return (0);
	return (kp_end(head, CH_END));
}

/*
**	-------------------------------------------------------------------------- +
**	Handles 'home' key, and 'ctrl + a' key combination (alias for 'home').
**	-------------------------------------------------------------------------- +
*/

int	kp_home(t_line **head, char ch)
{
	if (ch != CH_HOME)
		return (0);
	while ((*head)->cur_pos > 0)
		mc_left(*head);
	return (KEY_HOME);
}

int	kp_ctrl_a(t_line **head, char ch, int mode)
{
	(void)mode;
	if (ch != KP_CTRL_A)
		return (0);
	return (kp_home(head, CH_HOME));
}
