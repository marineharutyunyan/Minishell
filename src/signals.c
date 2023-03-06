#include "mini.h"

void signal_SIGINT_handler(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void handle_signals(int mode)
{
	if (mode == INTERACTIVE_MODE)
	{
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) 
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
	else
	{
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) 
		{
			perror("Failed to register signal handler");
			exit(1);
		}
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		{
			perror("Failed to register signal handler");
			exit(1);
		}

	}
	
}
