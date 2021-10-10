/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:21:37 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/10 23:21:38 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_exit.h"
#include "ft_vector.h"
#include "ft_io.h"
#include "ft_string.h"

//TODO print wrong argument

int	ms_exit(char *argv[], t_vector *env)
{
	long long	n;
	t_ft_err	err;

	(void)env;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv || !argv[0])
		return (1);
	if (!argv[1])
		ft_exit(0);
	if (argv[2])
	{
		ft_putstr_fd("mish: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	err = ft_strtol_m(argv[1], 9223372036854775807ull, &n);
	if (err)
	{
		ft_putstr_fd("mish: exit: numeric argument required\n", STDERR_FILENO);
		ft_exit(255);
	}
	ft_exit(n);
	return (1);
}
