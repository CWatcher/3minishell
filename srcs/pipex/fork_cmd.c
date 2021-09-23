/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:24:29 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/01 14:47:29 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "exit_me.h"

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
	char **const	search_dirs = ft_split(path_var, ':');
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
	ft_freestrs(search_dirs);
	return (found_pathname);
}

static void	exec_cmd(const char *cmd, char *envp[])
{
	char	**argv;
	char	*pathname;

	argv = ft_split(cmd, ' ');
	if (ft_strchr(argv[0], '/'))
		pathname = ft_strdup(argv[0]);
	else
		pathname = get_exec_pathname(argv[0], find_value(envp, "PATH="));
	execve(pathname, argv, envp);
	ft_freestrs(argv);
	exit_me(pathname);
}

pid_t	fork_cmd(const char *cmd, char *envp[], int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in >= 0 && dup2(fd_in, STDIN_FILENO) != STDIN_FILENO)
			exit_me(ft_strjoin("failed to dup2 on:", cmd));
		if (fd_out >= 0 && dup2(fd_out, STDOUT_FILENO) != STDOUT_FILENO)
			exit_me(ft_strjoin("failed to dup2 on:", cmd));
	}
	if (fd_in != STDIN_FILENO)
		if (close(fd_in) != 0)
			exit_me(ft_strdup("Failed to close(fd_in) in fork_cmd()"));
	if (fd_out != STDOUT_FILENO)
		if (close(fd_out) != 0)
			exit_me(ft_strdup("Failed to close(fd_out) in fork_cmd()"));
	if (pid == 0)
		exec_cmd(cmd, envp);
	if (pid < 0)
		exit_me(ft_strjoin("Failed to fork() on:", cmd));
	return (pid);
}
