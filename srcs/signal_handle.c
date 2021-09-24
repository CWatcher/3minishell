#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

void	new_line(int i)
{
	(void)i;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

void	ignore(int i)
{
	(void)i;
	rl_on_new_line();
	rl_redisplay();
	rl_done = 0;
}

int event(void)
{
	return 0;
}

void	set_signal_handler(void)
{
	rl_event_hook = event;
	signal(SIGINT, new_line);
	signal(SIGQUIT, ignore);
}
