/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:49 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 09:03:01 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"

typedef struct s_io_fds
{
	int		in;
	int		out;
}			t_io_fds;

int		ft_perror(const char *s, int ret);
pid_t	fork_cmd(t_command *cmd, t_ms_vars *vars, int fd_in, int fd_out);
t_bool	fork_heredoc(char *limiter, t_io_fds pipe);
int		run_builtin(t_builtin_func builtin_func, t_command *cmd, \
				t_ms_vars *vars);
int		run_pipeline(t_vector pipeline, t_ms_vars *vars);
int		fd_restore(int fd, int source_fd);

#endif
