#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

#include <stdlib.h>

void	new_line(int i)
{
	(void)i;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
}

void	set_signal_handler(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, SIG_IGN);
}
