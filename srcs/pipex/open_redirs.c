/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/09 20:06:47 by CWatcher         ###   ########.fr       */
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
		return (ft_false);
	return (ft_true);
}

t_bool	open_redirs(t_vector v_redirs, t_vector env,
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
		//! \todo error if open args return more then 1 arg
		t = open_arg(redirs[i].arg, &env);
		path = *t;
		*t = NULL;
		ft_strarr_clear(t);

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
