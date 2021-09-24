#include "tokenize.h"
#include <ft_string.h>

char *env_value(t_vector *env, t_stringview key)
{
	char	*str;
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		str = *(char **)ft_vec_at(env, i);
		if (ft_strncmp(str, key.str, key.size) == 0 && str[key.size] == '=')
		{
			return (str + key.size + 1);
		}
		i++;
	}
	return "";
}

t_error	get_name(t_stringview sv, t_stringview *name, size_t *pos)
{
	t_error	err;

	err = error_no_error;
	if (sv.str[*pos] == '{')
	{
		name->str = &sv.str[++(*pos)];
		name->size = 0;
		while (*pos < sv.size && sv.str[*pos] != '}')
		{
			if (!(ft_isalnum(name->str[name->size]) || name->str[name->size] == '_'))
				err = error_parse_error;
			name->size++;
			(*pos)++;
		}
		(*pos)++;
	}
	else
	{
		name->str = &sv.str[*pos];
		name->size = 0;
		while (ft_isalnum(name->str[name->size]) || name->str[name->size] == '_')
		{
			name->size++;
			(*pos)++;
		}
	}
	return (err);
}

t_error	open_arg_env(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
	t_stringview	name;
	char			*env_v;

	(*pos)++;
	if (get_name(sv, &name, pos))
		return (error_parse_error);
	if (name.size == 0)
	{
		if (ft_vec_push_back(str_build, "$") == t_false)
			return (error_allocation_fail);
	}
	else
	{
		env_v = env_value(env, name);
		if (ft_vec_push_back_n(str_build, env_v, ft_strlen(env_v)) == t_false)
			return (error_allocation_fail);
	}
	return (error_no_error);
}

t_error	open_argNquotes(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
	t_error	err;

	err = error_no_error;
	while (*pos < sv.size && '\"' != sv.str[*pos] && '\'' != sv.str[*pos])
	{
		if (sv.str[*pos] == '\\')
			(*pos)++;
		else if (sv.str[*pos] == '$')
			err = open_arg_env(sv, str_build, env, pos);
		else if (ft_vec_push_back(str_build, &sv.str[(*pos)++]) == t_false)
			return (error_allocation_fail);
		if (err)
			return (err);
	}
	return (error_no_error);
}

t_error	open_arg1quotes(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
	(void)env;
	(*pos)++;
	while (sv.str[*pos] != '\'')
	{
		if (ft_vec_push_back(str_build, &sv.str[*pos]) == t_false)
			return (error_allocation_fail);
		(*pos)++;
	}
	(*pos)++;
	return (error_no_error);
}

t_error	open_arg2quotes(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
	t_error	err;

	(void)env;
	err = error_no_error;
	(*pos)++;
	while (sv.str[*pos] != '\"')
	{
		if (sv.str[*pos] == '$')
			err = open_arg_env(sv, str_build, env, pos);
		else if (ft_vec_push_back(str_build, &sv.str[(*pos)++]) == t_false)
			return (error_allocation_fail);
		if (err)
			return (err);
	}
	(*pos)++;
	return (error_no_error);
}

char *open_arg(t_stringview sv, t_vector *env)
{
	t_vector	str_build;
	t_error		err;
	size_t		pos;
	char const	zero = '\0';

	ft_vec_construct(&str_build, sizeof(char));
	ft_vec_reserv(&str_build, sv.size * 1.3);
	pos = 0;
	while (pos < sv.size)
	{
		if (sv.str[pos] == '\"')
			err = open_arg2quotes(sv, &str_build, env, &pos);
		else if (sv.str[pos] == '\'')
			err = open_arg1quotes(sv, &str_build, env, &pos);
		else
			err = open_argNquotes(sv, &str_build, env, &pos);
		if (err)
		{
			ft_vec_destructor(&str_build, NULL);
			return (NULL);
		}
	}
	ft_vec_push_back(&str_build, (void*)&zero);
	return (ft_vec_fetch_array(&str_build, NULL));
}
