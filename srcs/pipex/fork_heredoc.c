/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:04:17 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 08:17:25 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"
#include "ft_io.h"
#include "pipex.h"
#include "minishell.h"
#include "ft_vector.h"
#include "ft_exit.h"

static void	pp_vec_destr(t_vector *v_pp)
{
	ft_vec_destructor(v_pp, (t_destr_func)ft_freederef);
}

t_ft_err	v_lines_load_heredoc(t_vector *pv_lines, char *limiter)
{
	int			r;
	char		*s;
	t_ft_err	err;

	ft_putstr("> ");
	err = 0;
	r = ft_get_next_line(STDIN_FILENO, &s);
	while (r > 0 && !err && ft_strncmp(limiter, s, ft_strlen(limiter) + 1) != 0)
	{
		err = ft_vec_push_back(pv_lines, &s);
		if (err)
			ms_perror("get_put_heredoc()", "ft_vec_push_back(, &s)", NULL, 1);
		else if (ft_putstr("> ") < 0)
			err = ms_perror("get_put_heredoc()", "ft_putstr(\"> \")", NULL, 1);
		r = ft_get_next_line(STDIN_FILENO, &s);
	}
	if (r < 0)
		err = ms_perror("get_put_heredoc()", "ft_get_next_line()", NULL, 1);
	s = NULL;
	err = ft_vec_push_back(pv_lines, &s);
	if (err)
		ms_perror("get_put_heredoc()", "ft_vec_push_back(, NULL)", NULL, 1);
	return (err);
}

static void	get_put_heredoc(char *limiter, int fd_out)
{
	t_vector	v_lines;
	t_ft_err	err;

	ft_vec_construct(&v_lines, sizeof(char *));
	ft_at_exit(&v_lines, (t_destr_func) pp_vec_destr);
	err = v_lines_load_heredoc(&v_lines, limiter);
	if (ft_putmultistr_fd(v_lines.array, fd_out) < 0)
		err = ms_perror("get_put_heredoc()", "ft_putmultistr_fd()", NULL, 1);
	if (close(fd_out) != 0)
		err = ms_perror("get_put_heredoc()", "close()", NULL, ft_err_fail);
	ft_exit(err);
}

t_bool	fork_heredoc(char *limiter, t_io_fds fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_at_exit(limiter, free);
		if (close(fds.in) != 0)
			ms_perror("child fork_heredoc()", "close(fds.in)", NULL, 1);
		get_put_heredoc(limiter, fds.out);
		ft_exit(0);
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
