#include "mini.h"

void	signal_sigint_handler(int signum)
{
	(void)signum;
	g_signal_notifire = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	print_and_exit(void)
{
	perror("Failed to register signal handler");
	exit(1);
}

void	handle_signals(int mode)
{
	if (mode == INTERACTIVE_MODE)
	{
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			print_and_exit();
		if (signal(SIGINT, signal_sigint_handler) == SIG_ERR)
			print_and_exit();
	}
	else
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			print_and_exit();

		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			print_and_exit();
	}
}
