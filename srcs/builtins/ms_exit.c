#include <unistd.h>
#include <stdlib.h>
#include "ft_vector.h"
#include "ft_io.h"
#include "ft_string.h"

int	ms_exit(char *argv[], t_vector *env)
{
	long long	n;
	t_ft_err	err;

	(void)env;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!argv || !argv[0])
		return (1);
	if (!argv[1])
		exit(0);
	if (argv[2])
	{
		ft_putstr_fd("mish: exit: too many arguments\n", STDERR_FILENO);
		exit(1);
	}
	err = ft_strtol_m(argv[1], 0x8000000000000000, &n);
	if (err)
	{
		ft_putstr_fd("mish: exit: num error", STDERR_FILENO);
		exit(1);
	}
	exit(n);
}
