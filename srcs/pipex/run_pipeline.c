/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 01:11:26 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h> //perror()
#include "../minishell.h"
#include "pipex.h"
#include "ft_string.h" // free_mutlistr()
#include "ftdef.h"

static pid_t	fork_pipeline(t_vector pipeline, t_ms_vars *vars)
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
		if (pipe(pipe_fds) != 0)
			return (ft_perror("mish: pipe error", -3));
		fork_cmd((t_command *)&cmds[j], vars, fd_in, pipe_fds[1]);
		fd_in = pipe_fds[0];
		j++;
	}
	pid = fork_cmd((t_command *)&cmds[j], vars, fd_in, fd_out);
	return (pid);
}

int	run_pipeline(t_vector pipeline, t_ms_vars *vars)
{
	const t_command		*cmds = pipeline.array;
	char				**argv;
	t_builtin_func		builtin_func;
	pid_t				pid;
	int					status;

	if (pipeline.size == 1)
	{
		argv = open_allargs(cmds[0].args, vars);
		builtin_func = find_builtin(argv[0]);
		if (builtin_func != NULL)
		{
			argv = ft_freemultistr(argv);
			return (run_builtin(builtin_func, (t_command *)&cmds[0], vars));
		}
		argv = ft_freemultistr(argv);
	}
	pid = fork_pipeline(pipeline, vars);
	if (pid < 0)
		return (1);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
