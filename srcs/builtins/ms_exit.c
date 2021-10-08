#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_io.h"

int	ms_exit(char *argv[])
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv || !argv[0])
		return (1);
	if (!argv[1])
		exit(0);
	if (argv[2])
	{
		ft_putstr_fd("mish: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (1);
}
