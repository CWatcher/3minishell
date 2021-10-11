/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:04:17 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/11 22:22:22 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_io.h"
#include "exit_me.h"
#include "pipex.h"
#include "minishell.h"

static void	get_put_heredoc(char *limiter, int fd_out)
{
	char		*s;
	int			r;

	ft_putstr("> ");
	r = ft_get_next_line(STDIN_FILENO, &s);
	while (r > 0 && ft_strncmp(limiter, s, ft_strlen(limiter) + 1) != 0)
	{
		r = ft_putendl_fd(s, fd_out);
		s = ft_free(s);
		if (r < 0)
			exit_me(ft_strdup("heredoc: failed to ft_putendl_fd()"));
		if (ft_putstr("> ") < 0)
			exit_me(ft_strdup("heredoc: failed to ft_putstr()"));
		r = ft_get_next_line(STDIN_FILENO, &s);
	}
	s = ft_free(s);
	free(limiter);
	if (close(fd_out) != 0)
		exit_me(ft_strdup("Failed to close() in get_put_heredoc()"));
	if (r < 0)
		exit_me(ft_strdup("heredoc: failed to ft_get_next_line()"));
}

t_bool	fork_heredoc(char *limiter, t_io_fds fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (close(fds.in) != 0)
			ms_perror("child fork_heredoc()", "close(fds.in)", NULL, 1);
		get_put_heredoc(limiter, fds.out);
		exit_me(NULL);
	}
	else
	{
		free(limiter);
		if (close(fds.out) != 0)
			ms_perror("parent fork_heredoc()", "close(fds.out)", NULL, ft_true);
		if (pid < 0)
			return (ms_perror("fork_heredoc()", "fork()", NULL, ft_false));
	}
	return (ft_true);
}
