/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_andor_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/01 10:24:47 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h> //perror()
#include "../minishell.h"
#include "fork_boost.h"
#include "ftdef.h"
#include "ft_string.h" // free_mutlistr()

t_bool	ft_open_file(const char *path, int oflag, int *p_fd)
{
	if (*p_fd > STDERR_FILENO)
		if (close(*p_fd) != 0)
			perror("ft_open_file(): close()");
	*p_fd = open(path, oflag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*p_fd == -1)
		return (t_false);
	return (t_true);
}

t_bool	open_redirs(const t_vector *v_redirs, const t_vector *env,
					int *p_fd_in, int *p_fd_out)
{
	size_t			i;
	const t_redir	*redirs = v_redirs->array;
	char			*path;
	t_bool			r;

	i = 0;
	r = t_true;
	while (r && i < v_redirs->size)
	{
		path = open_arg(redirs[i].arg, env);
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
char**	open_args(t_vector v_stringviews, t_vector env)
{
	const t_stringview	*stringviews = v_stringviews.array;
	size_t				i;
	char				**argv;

	i = 0;
	argv = malloc(sizeof(char *) * (v_stringviews.size + 1));
	if (!argv)
		return (NULL);
	while (i < v_stringviews.size)
	{
		argv[i] = open_arg(stringviews[i], &env);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	run_pipeline(const t_vector *pipeline, t_vector *env)
{
	const t_command		*cmds = pipeline->array;
	char				**argv;
	size_t				j;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	int					status;

	j = 0;
	while (j < pipeline->size)
	{
		fd_in = STDIN_FILENO;
		fd_out = STDOUT_FILENO;
		if (open_redirs(&cmds[j].redirs, env, &fd_in, &fd_out))
		{
			argv = open_args(cmds[j].args, *env);
			pid = fork_cmd(argv, env->array, fd_in, fd_out);
			argv = ft_freemultistr(argv);
			waitpid(pid, &status, 0);
		}
		j++;
	}
	return (WEXITSTATUS(status));
}
