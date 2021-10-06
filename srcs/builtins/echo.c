#include "../minishell.h"
#include "ft_io.h"

//int	echo(const args, t_vector env)
int	echo(char* argv[])
{
	t_bool		no_newline;
	const char 	*ending[2] = {"\n", ""};

	if (!argv || !argv[0] || !argv[1])
		return (0);
	no_newline = ft_strcmp(argv[1], "-n") == 0;
	if (ft_putmultistr_delim(argv + no_newline + 1, " ", ending[no_newline]) < 0)
		return (1);
	return (0);
}
