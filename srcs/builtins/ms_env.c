#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ft_vector.h>
#include <ft_io.h>
#include <ft_string.h>

static void	print_env(t_vector *envv)
{
	char const	**env = envv->array;
	size_t		i;

	i = 0;
	while (env[i])
		ft_putendl(env[i++]);
}

int	ms_env(char *argv[], t_vector *env)
{
	if (argv[1] != NULL)
	{
		ft_err_perror("env: ", ft_err_toomanyargs);
		return (1);
	}
	print_env(env);
	return (0);
}
