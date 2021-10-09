#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

#include <stdlib.h>
#include <unistd.h>
#include <ft_io.h>
#include <ft_string.h>

static void	new_line(int i)
{
	(void)i;
	ft_putendl("");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	clean_quit(int code)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(code, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
}

void	set_signal_handler(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, SIG_IGN);
}

static void	clean_int(int i)
{
	(void)i;
}

void	clean_signal_handlers(void)
{
	clean_int(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, clean_quit);
}
