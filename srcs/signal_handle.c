#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <ft_io.h>
#include <ft_string.h>

static void	sig_handle(int sig)
{
	int		status;

	waitpid(-1, &status, 0);
	if (WTERMSIG(status) == SIGINT && WIFSIGNALED(status))
		rl_on_new_line();
	else if (sig == SIGINT)
	{
		ft_putstr("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (WTERMSIG(status) == SIGQUIT && WIFSIGNALED(status))
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
	}
	return ;
}

void	set_sig_handler(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	set_exesig_handler(void)
{
	signal(SIGQUIT, sig_handle);
}
