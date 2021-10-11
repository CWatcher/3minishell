/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:21:37 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/11 18:46:23 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_exit.h"
#include "ft_vector.h"
#include "ft_io.h"
#include "ft_string.h"
#include "minishell.h" //ms_perror()

int	ms_exit(char *argv[], t_vector *env)
{
	long long	n;
	t_ft_err	err;
	char		*arg;

	(void)env;
	arg = NULL;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv[1])
		ft_exit(0);
	if (argv[2])
		return (ms_perror(argv[0], argv[1], "too many arguments", 1));
	arg = ft_strtrim(argv[1], " \t\n\v\f\r");
	err = ft_strtol_m(argv[1], 9223372036854775808ull, &n);
	if (err || ft_strcmp_s(arg, "9223372036854775808") == 0)
	{
		free(arg);
		ft_exit(ms_perror(argv[0], argv[1], "numeric argument required", 255));
	}
	free(arg);
	ft_exit(n);
	return (1);
}

//RF ft_strtrim(); ft_strcmp_s() -> strstr()
