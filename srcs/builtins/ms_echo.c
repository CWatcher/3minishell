#include "../minishell.h"
#include <ft_vector.h>
#include "ft_io.h"

int	ms_echo(char *argv[], t_vector *env)
{
	t_bool		newline_on;

	(void)env;
	if (!argv || !argv[0])
		return (0);
	newline_on = ft_strcmp_s(argv[1], "-n") != 0;
	if (ft_putmultistr_delim(argv + !newline_on + 1, " ") < 0)
		return (1);
	if (newline_on)
		ft_putstr("\n");
	return (0);
}
