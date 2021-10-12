/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 07:11:52 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:11:52 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_arg.h"
#include "../minishell.h"

t_ft_err	push_env_to_args_spaces(t_open_arg *oa, char *env_v, size_t *pos)
{
	char	*str;

	if (oa->str_build.size != 0)
	{
		if (ft_vec_push_back(&oa->str_build, "\0") != ft_err_ok)
			return (ft_err_bad_alloc);
		str = ft_vec_fetch_array(&oa->str_build, NULL);
		if (ft_vec_push_back(&oa->arg_build, &str) != ft_err_ok)
			return (ft_err_bad_alloc);
	}
	while (ft_isspace(env_v[*pos]))
		(*pos)++;
}

t_ft_err	push_env_to_args(t_open_arg *oa, char *env_v)
{
	size_t	pos;

	pos = 0;
	while (env_v[pos])
	{
		if (ft_isspace(env_v[pos]))
		{
			if (push_env_to_args_spaces(oa, env_v, &pos) != ft_err_ok)
				return (ft_err_bad_alloc);
		}
		else
		{
			if (ft_vec_push_back(&oa->str_build, &env_v[pos]) != ft_err_ok)
				return (ft_err_bad_alloc);
			pos++;
		}
	}
	return (ft_err_ok);
}

t_ft_err	open_arg_env(t_open_arg *oa, const t_ms_vars *vars)
{
	t_stringview	name;
	t_ft_err		err;
	char			*env_v;

	(oa->pos)++;
	err = choose_name(oa, &name);
	if (err != ft_err_ok)
		return (err);
	if (name.size == 0)
	{
		if (ft_vec_push_back(&oa->str_build, "$") != ft_err_ok)
			return (ft_err_bad_alloc);
	}
	else
	{
		env_v = env_value(name, vars);
		if (push_env_to_args(oa, env_v) != ft_err_ok)
			return (ft_err_bad_alloc);
	}
	return (ft_err_ok);
}

t_ft_err	open_arg_env_quotes(t_open_arg *oa, const t_ms_vars *vars)
{
	t_stringview	name;
	t_ft_err		err;
	char			*env_v;

	(oa->pos)++;
	err = choose_name(oa, &name);
	if (err != ft_err_ok)
		return (err);
	if (name.size == 0)
	{
		if (ft_vec_push_back(&oa->str_build, "$") != ft_err_ok)
			return (ft_err_bad_alloc);
	}
	else
	{
		env_v = env_value(name, vars);
		if (ft_vec_push_back_n(&oa->str_build, env_v, ft_strlen(env_v)) \
				!= ft_err_ok)
			return (ft_err_bad_alloc);
	}
	return (ft_err_ok);
}

t_ft_err	open_argnoquotes(t_open_arg *oa, const t_ms_vars *vars)
{
	t_ft_err	err;

	err = ft_err_ok;
	while (oa->pos < oa->sv.size \
			&& '\"' != oa->sv.str[oa->pos] \
			&& '\'' != oa->sv.str[oa->pos])
	{
		if (oa->sv.str[oa->pos] == '\\')
		{
			oa->pos++;
			if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++]) \
					!= ft_err_ok)
				err = ft_err_bad_alloc;
		}
		else if (oa->sv.str[oa->pos] == '$')
			err = open_arg_env(oa, vars);
		else if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++]) \
					!= ft_err_ok)
			err = ft_err_bad_alloc;
		if (err != ft_err_ok)
			return (err);
	}
	return (ft_err_ok);
}
