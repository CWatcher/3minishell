/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:51:44 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 06:59:27 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "ft_io.h"

int	ms_perror(const char *cmd, const char *arg, \
				const char *msg, int ret)
{
	ft_putstr_fd_s("mish: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd_s(cmd, STDERR_FILENO);
		ft_putstr_fd_s(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd_s(arg, STDERR_FILENO);
		ft_putstr_fd_s(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putendl_fd_s(msg, STDERR_FILENO);
	else if (errno)
		perror("");
	else if (cmd || arg)
		ft_putstr_fd_s("\n", STDERR_FILENO);
	return (ret);
}
