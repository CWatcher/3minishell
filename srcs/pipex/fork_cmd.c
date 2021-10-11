/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:24:29 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 00:55:31 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../minishell.h"
#include "pipex.h"
#include "ft_string.h"
#include "ft_exit.h"
#include <sys/types.h>

static char	*find_value(char *vars[], char *var_name_with_delimiter)
{
	const ssize_t	var_name_w_d_l = ft_strlen(var_name_with_delimiter);

	while (*vars && ft_strncmp(*vars, var_name_with_delimiter, var_name_w_d_l))
		vars++;
	if (!*vars)
		return (NULL);
	return (*vars + var_name_w_d_l);
}

static char	*get_exec_pathname(const char *filename, const char *path_var)
{
	char **const	search_dirs = ft_split(path_var, ":");
	char			*pathname;
	char			*found_pathname;
	char			**dir;
	int				r;

	dir = search_dirs;
	r = -1;
	found_pathname = ft_strdup(filename);
	while (*dir && r == -1)
	{
		if ((*dir)[ft_strlen(*dir)] != '/')
			ft_strappend(dir, "/");
		pathname = ft_strjoin(*dir, filename);
		r = access(pathname, X_OK);
		if (r == 0 || errno != ENOENT)
			ft_reassign((void **)&found_pathname, pathname);
		else
			pathname = ft_free(pathname);
		dir++;
	}
	ft_freemultistr(search_dirs);
	return (found_pathname);
}

static void	exec_cmd(t_command *cmd, t_ms_vars *vars)
{
	char			*pathname;
	char			**argv;
	t_builtin_func	builtin_func;
	t_io_fds		fds;

	fds = (t_io_fds) {STDIN_FILENO, STDOUT_FILENO};
	pathname = NULL;
	argv = open_allargs(cmd->args, vars);
	if (!argv)
		ft_exit(ms_perror("open_allargs()", ((char**)cmd->args.array)[0], NULL, 1));
	if (!open_redirs(cmd->redirs, vars, &fds.in, &fds.out))
		ft_exit(1);
	 if (fd_restore(STDIN_FILENO, fds.in) < 0
	 	|| fd_restore(STDOUT_FILENO, fds.out) < 0)
		 ft_exit(1);
	if (ft_strchr(argv[0], '/'))
		pathname = ft_strdup(argv[0]);
	else
	{
		builtin_func = find_builtin(argv[0]);
		if (builtin_func != NULL)
			(ft_exit(builtin_func(argv, &vars->env)));
		else
			pathname = get_exec_pathname(argv[0], find_value(vars->env.array, "PATH="));
	}
	execve(pathname, argv, vars->env.array);
	argv = ft_freemultistr(argv);
	ft_at_exit(pathname, (t_destr_func)free);
	ft_exit(ms_perror(pathname, NULL, strerror(errno), 127));
}
	//TODO check exit codes when argv[0] is a dir, ...

pid_t	fork_cmd(t_command *cmd, t_ms_vars *vars, int fd_in, int fd_out)
{
	pid_t	pid;
	char 	*const *argv = cmd->args.array;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) != STDIN_FILENO)
			ft_exit(ms_perror("mish: dup2()", NULL, NULL, 1));
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) != STDOUT_FILENO)
			ft_exit(ms_perror("mish: dup2()", NULL, NULL, 1));
		exec_cmd(cmd, vars);
	}
	errno = 0;
	if (fd_in != STDIN_FILENO && close(fd_in) != 0)
		ms_perror("fork_cmd(): close(fd_in)", argv[0], NULL, 1);
	if (fd_out != STDOUT_FILENO && close(fd_out) != 0)
		ms_perror("fork_cmd(): close(fd_out)", argv[0], NULL, 1);
	if (errno != 0 && pid == 0)
		ft_exit(ms_perror("mish: child", NULL, NULL, 1));
	if (pid < 0)
		perror("mish: fork()");
	return (pid);
}
