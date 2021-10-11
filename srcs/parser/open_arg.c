/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:40:17 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 01:23:00 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <ft_string.h>

typedef struct s_open_arg {
	t_vector		arg_build;
	t_vector		str_build;
	t_stringview	sv;
	size_t			pos;
}			t_open_arg;

char	*get_intvalue(int value)
{
	static char	arr[32];

	ft_utob(arr, value);
	return arr;
}

char *env_value(t_stringview key, const t_ms_vars *vars)
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
	return "";
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

t_ft_err	push_env_to_args(t_open_arg *oa, char *env_v)
{
	size_t	pos;
	char	*str;

	pos = 0;
	while (env_v[pos])
	{
		if (ft_isspace(env_v[pos]))
		{
			if (oa->str_build.size != 0)
			{
				if (ft_vec_push_back(&oa->str_build, "\0") != ft_err_ok)
					return (ft_err_bad_alloc);
				str = ft_vec_fetch_array(&oa->str_build, NULL);
				if (ft_vec_push_back(&oa->arg_build, &str) != ft_err_ok)
					return (ft_err_bad_alloc);
			}
			while (ft_isspace(env_v[pos]))
				pos++;
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
		if (ft_vec_push_back_n(&oa->str_build, env_v, ft_strlen(env_v))
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

t_ft_err	open_arg1quotes(t_open_arg *oa)
{
	(oa->pos)++;
	while (oa->sv.str[oa->pos] != '\'')
	{
		if (ft_vec_push_back(&oa->str_build, &oa->sv.str[oa->pos]) != ft_err_ok)
			return (ft_err_bad_alloc);
		(oa->pos)++;
	}
	(oa->pos)++;
	return (ft_err_ok);
}

t_ft_err	open_arg2quotes(t_open_arg *oa, const t_ms_vars *vars)
{
	t_ft_err	err;

	err = ft_err_ok;
	oa->pos++;
	while (oa->sv.str[oa->pos] != '\"')
	{
		if (oa->sv.str[oa->pos] == '$')
			err = open_arg_env_quotes(oa, vars);
		else if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++])
						!= ft_err_ok)
			return (ft_err_bad_alloc);
		if (err)
			return (err);
	}
	(oa->pos)++;
	return (ft_err_ok);
}

t_ft_err	real_open_arg(t_open_arg *oa, const t_ms_vars *vars)
{
	t_ft_err		err;

	while (oa->pos < oa->sv.size)
	{
		if (oa->sv.str[oa->pos] == '\"')
			err = open_arg2quotes(oa, vars);
		else if (oa->sv.str[oa->pos] == '\'')
			err = open_arg1quotes(oa);
		else
			err = open_argnoquotes(oa, vars);
		if (err != ft_err_ok)
			return (err);
	}
	return (ft_err_ok);
}

static void	*clean_open_arg(t_open_arg *oa, t_ft_err err)
{
	ft_err_perror("mish: ", err);
	ft_vec_destructor(&oa->str_build, NULL);
	ft_vec_destructor(&oa->arg_build, (t_destr_func)ft_freederef);
	return (NULL);
}

char	**open_arg(t_stringview sv, const t_ms_vars *vars)
{
	t_open_arg		oa;
	t_ft_err		err;
	char			*str;

	oa.pos = 0;
	oa.sv = sv;
	ft_vec_construct(&oa.str_build, sizeof(char));
	ft_vec_reserv(&oa.str_build, sv.size);
	ft_vec_construct(&oa.arg_build, sizeof(char*));
	err = real_open_arg(&oa, vars);
	if (err != ft_err_ok)
		return (clean_open_arg(&oa, err));
	err = ft_err_ok;
	if (oa.str_build.size != 0 || oa.arg_build.size == 0)
	{
		ft_vec_push_back(&oa.str_build, "\0");
		str = ft_vec_fetch_array(&oa.str_build, NULL);
		err = ft_vec_push_back(&oa.arg_build, &str);
		if (err != ft_err_ok)
			free(str);
	}
	str = NULL;
	err |= ft_vec_push_back(&oa.arg_build, &str);
	if (err != ft_err_ok)
		return (clean_open_arg(&oa, ft_err_bad_alloc));
	return (ft_vec_fetch_array(&oa.arg_build, NULL));
}
