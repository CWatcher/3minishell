/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:05:01 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/30 22:27:29 by CWatcher         ###   ########.fr       */
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
		ft_putendl_fd(dynamic_error, STDERR_FILENO);
		status = EXIT_FAILURE;
	}
	free(dynamic_error);
	exit(status);
}
