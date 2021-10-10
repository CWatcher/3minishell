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
			return (ft_perror("mish: dup(fd_backup):", -1));
		if (fd >= 0 && dup2(target_fd, fd) != fd)
			return (ft_perror("mish: dup2(target_fd, fd):", -1));
	}
	return (fd_backup);
}

static int fd_restore(int fd, int target_fd)
{
	if (fd != target_fd)
	{
		if (fd >= 0 && dup2(target_fd, fd) != fd)
			return (ft_perror("mish: fd_restore():", -1));
		if (close(fd) != 0)
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
	if (std_out_backup < 0)
		return (-1);
	argv = open_allargs(args, *env);
	r = builtin_func(argv, env);
	
	fd_restore(std_in_backup, STDIN_FILENO);
	fd_restore(std_out_backup, STDOUT_FILENO);
	return (r);
}
