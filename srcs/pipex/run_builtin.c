#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h> //perror()
#include "../minishell.h"
#include "pipex.h"
#include "ft_string.h" // free_mutlistr()
#include "ftdef.h"

static int	fd_redirect(int fd, int target_fd)
{
	int	fd_backup;

	fd_backup = fd;
	if (fd != target_fd)
	{
		fd_backup = dup(fd);
		if (fd_backup < 0)
			return (ft_perror("mish: fd_redirect(): dup()", -1));
		if (dup2(target_fd, fd) != fd)
			return (ft_perror("mish: fd_redirect(): dup2()", -1));
		if (close(target_fd) != 0)
			return (ft_perror("mish: fd_redirect(): close()", -1));
	}
	return (fd_backup);
}

static int	fd_restore(int fd, int source_fd)
{
	if (fd != source_fd)
	{
		if (dup2(source_fd, fd) != fd)
			return (ft_perror("mish: fd_restore(): dup2()", -1));
		if (close(source_fd) != 0)
			return (ft_perror("mish: fd_restore(): close()", -1));
	}
	return (fd);
}

int	run_builtin(t_builtin_func builtin_func, t_vector args, t_vector redirs,
				t_vector *env)
{
	int	fd_in;
	int	fd_out;
	int	std_in_backup;
	int	std_out_backup;
	int	r;
	char	**argv;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (!open_redirs(redirs, env, &fd_in, &fd_out))
		return (-1);
	std_in_backup = fd_redirect(STDIN_FILENO, fd_in);
	std_out_backup = fd_redirect(STDOUT_FILENO, fd_out);
	if (std_in_backup || std_out_backup < 0)
		return (-1);
	argv = open_allargs(args, *env);
	//TODO check argv everywhere
	if (argv == NULL)
		return (1);
	r = builtin_func(argv, env);
	argv = ft_freemultistr(argv);
	fd_restore(STDIN_FILENO, std_in_backup);
	fd_restore(STDOUT_FILENO, std_out_backup);
	return (r);
}
