#include "../minishell.h"
#include "ft_string.h"

t_builtin_func	find_builtin(const char *s)
{
	if (ft_strcmp_s(s, "echo") == 0)
		return ((t_builtin_func)echo);
	else
		return (NULL);
}
