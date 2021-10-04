/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_boost.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:45:47 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/04 19:40:40 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_BOOST_H
# define FORK_BOOST_H

# include <sys/types.h>
# include "../minishell.h"

pid_t	fork_cmd(t_vector args, t_vector env, int fd_in, int fd_out);
void	fork_heredoc(const char *limiter, int fd_out);

#endif
