/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/11 19:40:52 by CWatcher         ###   ########.fr       */
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


static t_bool	ft_open_file(const char *path, int oflag, int *p_fd)
{
	if (*p_fd > STDERR_FILENO)
		if (close(*p_fd) != 0)
			perror("ft_open_file(): close()");
	*p_fd = open(path, oflag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*p_fd == -1)
	{
		ms_perror(NULL, path, NULL, 1);
		return (ft_false);
	}
	return (ft_true);
}

int	fd_restore(int fd, int source_fd)
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

t_bool	open_redirs(t_vector v_redirs, const t_vector *env,
					int *p_fd_in, int *p_fd_out)
{
	size_t			i;
	const t_redir	*redirs = v_redirs.array;
	char			*path;
	char			**t;
	t_bool			r;

	i = 0;
	r = ft_true;
	while (r && i < v_redirs.size)
	{
		t = open_arg(redirs[i].arg, env);
		path = *t;
		*t = NULL;
		if (!t || t[1])
		{
			t = ft_freemultistr(t);
			return (ms_perror(NULL, redirs[i].arg.str, "ambiguous redirect", ft_false));
		}
		t = ft_freemultistr(t);
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
