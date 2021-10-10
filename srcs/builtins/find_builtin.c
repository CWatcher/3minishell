#include "../minishell.h"
#include "ft_string.h"

t_builtin_func	find_builtin(const char *s)
{
	const t_builtin_entry	builtin_dic[] = {
		{"echo", ms_echo},
		{"exit", ms_exit},
		{"export", ms_export},
		{"unset", ms_unset},
		{"env", ms_env},
		{NULL, NULL}};
	int						i;

	i = 0;
	while (builtin_dic[i].name && ft_strcmp(s, builtin_dic[i].name) != 0)
		i++;
	return (builtin_dic[i].func);
}
