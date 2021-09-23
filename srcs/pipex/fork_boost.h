/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_boost.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:45:47 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/23 21:58:43 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_BOOST_H
# define FORK_BOOST_H

pid_t	fork_cmd(const char *cmd, char *envp[], int fd_in, int fd_out);
pid_t	fork_pipeline(char *cmds[], char *envp[], int fd_in, int fd_out);
void	fork_heredoc(const char *limiter, int fd_out);

#endif
