/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:43:50 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 03:10:53 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_string.h"

t_builtin_func	find_builtin(const char *s)
{
	const t_builtin_entry	builtin_dic[] = {\
		{"echo", ms_echo}, \
		{"exit", ms_exit}, \
		{"export", ms_export}, \
		{"unset", ms_unset}, \
		{"env", ms_env}, \
		{"cd", ms_cd}, \
		{NULL, NULL}};
	int						i;

	i = 0;
	while (builtin_dic[i].name && ft_strcmp(s, builtin_dic[i].name) != 0)
		i++;
	return (builtin_dic[i].func);
}
