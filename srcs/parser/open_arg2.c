/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 07:09:05 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:09:46 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "open_arg.h"

static char	*get_intvalue(int value)
{
	static char	arr[32];

	ft_utob(arr, value);
	return (arr);
}

char	*env_value(t_stringview key, const t_ms_vars *vars)
{
	char	*str;
	size_t	i;

	if (key.size == 1 && ft_strncmp("?", key.str, 1) == 0)
		return (get_intvalue(vars->status));
	i = 0;
	while (i < vars->env.size - 1)
	{
		str = *(char **)ft_vec_at(&vars->env, i);
		if (ft_strncmp(str, key.str, key.size) == 0 && str[key.size] == '=')
		{
			return (str + key.size + 1);
		}
		i++;
	}
	return ("");
}

t_ft_err	choose_name_brack(t_open_arg *oa, t_stringview *name)
{
	name->str = &oa->sv.str[++(oa->pos)];
	name->size = 0;
	if (oa->sv.str[oa->pos] == '?' && oa->sv.str[oa->pos + 1] == '}')
	{
		name->size = 1;
		oa->pos += 2;
		return (ft_err_ok);
	}
	while (oa->pos < oa->sv.size && oa->sv.str[oa->pos] != '}')
	{
		if ((ft_isalnum(name->str[name->size]) \
				|| name->str[name->size] == '_') == ft_false)
			return (ft_err_bad_substitution);
		name->size++;
		(oa->pos)++;
	}
	(oa->pos)++;
	return (ft_err_ok);
}

t_ft_err	choose_name_nobrack(t_open_arg *oa, t_stringview *name)
{
	name->str = &oa->sv.str[oa->pos];
	name->size = 0;
	if (oa->sv.str[oa->pos] == '?')
	{
		name->size = 1;
		oa->pos++;
		return (ft_err_ok);
	}
	while (ft_isalnum(name->str[name->size]) \
			|| name->str[name->size] == '_')
	{
		name->size++;
		(oa->pos)++;
	}
	return (ft_err_ok);
}

t_ft_err	choose_name(t_open_arg *oa, t_stringview *name)
{
	if (oa->sv.str[oa->pos] == '{')
		return (choose_name_brack(oa, name));
	else
		return (choose_name_nobrack(oa, name));
}
