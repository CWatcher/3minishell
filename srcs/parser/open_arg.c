#include "tokenize.h"

t_error	open_arg1quotes(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
	while (*pos < sv.size && ft_strchr("\"'", sv.str[*pos]) == t_false)
	{
		if (ft_vec_push_back(str_build, &sv.str[*pos]) == t_false)
			return (error_allocation_fail);
		(*pos)++;
	}
	return (error_no_error);
}

t_error	open_arg1quotes(t_stringview sv, t_vector *str_build, t_vector *env, size_t *pos)
{
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
	(*pos)++;
	while (sv.str[*pos] != '"')
	{
		if (ft_vec_push_back(str_build, &sv.str[*pos]) == t_false)
			return (error_allocation_fail);
		(*pos)++;
	}
	(*pos)++;
	return (error_no_error);
}

char *open_arg(t_stringview sv, t_vector *env)
{
	t_vector	str_build;
	size_t		pos;
	char const	zero = '\0';

	ft_vec_construct(&str_build, sizeof(char));
	ft_vec_reserv(&str_build, sv.size * 1.3);
	pos = 0;
	while (pos < sv.size)
	{
		if (sv.str[pos] == '"')
			open_arg2quotes(sv, &str_build, env, &pos);
		else if (sv.str[pos] == '\'')
			open_arg1quotes(sv, &str_build, env, &pos);
		else
			open_argnquotes(sv, &str_build, env, &pos);
	}
	ft_vec_push_back(&str_build, &zero);
	return (ft_vec_fetch_array(&str_build, NULL));
}
