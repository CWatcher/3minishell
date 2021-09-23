/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:04:17 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/23 22:59:26 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_io.h"
#include "exit_me.h"

static void	get_put_heredoc(const char *limiter, int fd_out)
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
	if (close(fd_out) != 0)
		exit_me(ft_strdup("Failed to close() in get_put_heredoc()"));
	if (r < 0)
		exit_me(ft_strdup("heredoc: failed to ft_get_next_line()"));
}

void	fork_heredoc(const char *limiter, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		get_put_heredoc(limiter, fd_out);
		exit_me(NULL);
	}
	else if (pid > 0)
	{
		if (close(fd_out) != 0)
			exit_me(ft_strdup("Failed to close() in fork_heredoc()"));
	}
	else if (pid < 0)
		exit_me(ft_strjoin("Failed to fork() on here_doc ", limiter));
}
