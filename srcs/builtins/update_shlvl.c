/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 08:26:56 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 08:26:56 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_intvalue(int value)
{
	static char	arr[32];

	ft_utob(arr, value);
	return (arr);
}

static char	*get_env_value(t_stringview key, const t_vector *env)
{
	char	*str;
	size_t	i;

	i = 0;
	while (i < env->size - 1)
	{
		str = *(char **)ft_vec_at(env, i);
		if (ft_strncmp(str, key.str, key.size) == 0 && str[key.size] == '=')
		{
			return (str + key.size + 1);
		}
		i++;
	}
	return ("");
}

static int	str_find(char const **env_s, char const *ref)
{
	size_t	ref_len;

	if (*env_s == NULL)
		return (1);
	ref_len = ft_strlen(ref);
	return (!(ft_strncmp(*env_s, ref, ref_len) == 0 \
				&& (*env_s)[ref_len] == '='));
}

static char	*build_env(int value)
{
	return (ft_strjoin("SHLVL=", get_intvalue(value)));
}

t_ft_err	update_shlvl(t_vector *env)
{
	int		value;
	char	*str;

	value = ft_atoi(get_env_value(\
			(t_stringview){.str = "SHLVL", .size = 5}, env));
	value++;
	ft_vec_remove_all(env, "SHLVL", \
		(t_destr_func)ft_freederef, (t_cmp_func)str_find);
	str = build_env(value);
	ft_vec_insert(env, &str, env->size - 1);
	return (ft_err_ok);
}
