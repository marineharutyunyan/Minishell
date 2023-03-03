#include "mini.h"

void    signal_SIGQUIT_handler(int sig)
{
	printf("Ctrl + backslash\n");
	// Do nothing to ignore the signal
}

void signal_SIGINT_handler(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void handle_signals()
{
	if (signal(SIGQUIT, signal_SIGQUIT_handler) == SIG_ERR)
	{
		perror("Failed to register signal handler");
		exit(1);
	}
	if (signal(SIGINT, signal_SIGINT_handler) == SIG_ERR)
	{
		perror("Failed to register signal handler");
		exit(1);
	}
}
