/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:24:29 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/09 20:01:08 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "../minishell.h"
#include "pipex.h"
#include "ft_string.h"
#include "exit_me.h"
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

static void	exec_cmd(t_vector args, t_vector env) //TODO *env
{
	char			*pathname;
	char			*const *argv = open_allargs(args, env);
	t_builtin_func	builtin_func;

	if (ft_strchr(argv[0], '/'))
		pathname = ft_strdup(argv[0]);
	else
	{
		builtin_func = find_builtin(argv[0]);
		if (builtin_func != NULL)
			exit(builtin_func(args, &env));
		else
			pathname = get_exec_pathname(argv[0], find_value(env.array, "PATH="));
	}
	execve(pathname, argv, env.array);
	//TODO check exit codes when argv[0] is a dir
	//TODO free(ms)
	exit_me(pathname);
}

pid_t	fork_cmd(t_vector args, t_vector env, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) != STDIN_FILENO)
			exit_me(ft_strdup("mish: dup2()"));
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) != STDOUT_FILENO)
			exit_me(ft_strdup("mish: dup2()"));
		exec_cmd(args, env);
	}
	errno = 0;
	if (fd_in != STDIN_FILENO && close(fd_in) != 0)
		perror("mish: fork_cmd(): close(fd_in)");
	if (fd_out != STDOUT_FILENO && close(fd_out) != 0)
		perror("mish: fork_cmd(): close(fd_out)");
	if (errno != 0 && pid == 0)
		exit_me(ft_strdup("mish: child"));
	if (pid < 0)
		perror("mish: fork()");
	return (pid);
}
