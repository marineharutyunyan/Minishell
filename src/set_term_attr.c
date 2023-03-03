#include "mini.h"

void	set_term_attr(int on_off)
{
	struct termios	termios_p;

	tcgetattr(0, &termios_p);
	if (on_off == 1)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	else if (on_off == 0)
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
}