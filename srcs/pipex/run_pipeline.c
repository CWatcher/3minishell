/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/04 21:40:43 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h> //perror()
#include "../minishell.h"
#include "fork_boost.h"
#include "ft_string.h" // free_mutlistr()
#include "ftdef.h"

static t_bool	ft_open_file(const char *path, int oflag, int *p_fd)
{
	if (*p_fd > STDERR_FILENO)
		if (close(*p_fd) != 0)
			perror("ft_open_file(): close()");
	*p_fd = open(path, oflag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*p_fd == -1)
		return (t_false);
	return (t_true);
}

static t_bool	open_redirs(t_vector v_redirs, t_vector env,
					int *p_fd_in, int *p_fd_out)
{
	size_t			i;
	const t_redir	*redirs = v_redirs.array;
	char			*path;
	t_bool			r;

	i = 0;
	r = t_true;
	while (r && i < v_redirs.size)
	{
		path = open_arg(redirs[i].arg, &env);
		if (redirs[i].type == e_redir_i_stream)
		{
			// fork_heredoc()
			//*p_fd_in = heredoc_pipe[0];
		}
		else if (redirs[i].type == e_redir_i_file)
			r = ft_open_file(path, O_RDONLY, p_fd_in);
		else if (redirs[i].type == e_redir_o_trunc)
			r = ft_open_file(path, O_CREAT | O_WRONLY | O_TRUNC, p_fd_out);
		else if (redirs[i].type == e_redir_o_append)
			r = ft_open_file(path, O_CREAT | O_WRONLY | O_APPEND, p_fd_out);
		free(path);
		i++;
	}
	return (r);
}

static int	ft_perror(const char *s, int ret)
{
	perror(s);
	return (ret);
}

static pid_t	fork_pipeline(t_vector pipeline, t_vector env)
{
	const t_command		*cmds = pipeline.array;
	size_t				j;
	int					fd_in;
	int					fd_out;
	int					pipe_fds[2];
	pid_t				pid;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	j = 0;
	while (j < pipeline.size - 1)
	{
		if (!open_redirs(cmds[j].redirs, env, &fd_in, &fd_out))
			return (-1);
		if (fd_out != STDOUT_FILENO)
			if (close(fd_out) != 0)
				return (ft_perror("mish: fork_pipeline(): close() error", -2));
		if (pipe(pipe_fds) != 0)
			return (ft_perror("mish: pipe error", -3));
		fork_cmd(cmds[j].args, env, fd_in, pipe_fds[1]);
		fd_in = pipe_fds[0];
		j++;
	}
	pid = fork_cmd(cmds[j].args, env, fd_in, fd_out);
	return (pid);
}

int	run_pipeline(t_vector pipeline, t_vector env)
{
	pid_t				pid;
	int					status;

	pid = fork_pipeline(pipeline, env);
	if (pid < 0)
		return (1);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
