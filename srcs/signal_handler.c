#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	Executed when an INT ("interrupt") signal has been received in the program
**	(main loop). This causes the process to terminate.
**	It also sends a custom byte in the input queue, which call a function that..
**	-------------------------------------------------------------------------- +
*/

void	sig_int(int sig)
{
	char	byte[2];

	if (sig == SIGINT)
	{
		byte[0] = KP_CTRL_C;
		byte[1] = '\0';
		ioctl(STDIN_FILENO, TIOCSTI, byte);
	}
}

/*
**	-------------------------------------------------------------------------- +
**	Does nothing on TSTP ("terminal stop") signals.
**	-------------------------------------------------------------------------- +
*/

void	sig_exe(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDIN_FILENO);
}

/*
**	-------------------------------------------------------------------------- +
**	Kills all running processes before exiting, on kill signals.
**	-------------------------------------------------------------------------- +
*/

void	sig_kill(int sig)
{
	free_hist(&g_hist);
	def_term_mode(TERM_RESET);
	kill(0, sig);
	exit(sig);
}

/*
**	-------------------------------------------------------------------------- +
**	Initializes all signal handling functions needed.
**	-------------------------------------------------------------------------- +
*/

void	signal_handler(void)
{
	signal(SIGHUP, sig_kill);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_kill);
	signal(SIGABRT, sig_kill);
	signal(SIGALRM, sig_kill);
	signal(SIGTERM, sig_kill);
	signal(SIGTSTP, SIG_IGN);
}
