/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:05:01 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/08 19:41:41 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "ft_io.h"

void	exit_me(char *dynamic_error)
{
	int	status;

	//TODO free minishell
	if (!dynamic_error)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno)
	{
		perror(dynamic_error);
		status = errno;
	}
	else
	{
		ft_putendl_fd_s(dynamic_error, STDERR_FILENO);
		status = EXIT_FAILURE;
	}
	free(dynamic_error);
	exit(status);
}
