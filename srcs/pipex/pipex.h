/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:49 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/11 16:26:44 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"

typedef struct s_io_fds
{
	int	in;
	int	out;
}	t_io_fds;

int		ft_perror(const char *s, int ret);
pid_t	fork_cmd(t_vector args, t_vector redirs, t_vector *env, int fd_in, int fd_out);
int		run_builtin(t_builtin_func builtin_func, t_vector args, t_vector redirs,
				t_vector *env);
int		run_pipeline(t_vector pipeline, t_vector *env);
int		fd_restore(int fd, int source_fd);

#endif
