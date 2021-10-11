/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:48:16 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:06:43 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vector.h>
#include <ft_io.h>
#include <ft_string.h>

static int	str_find(char const **env_s, char const* ref)
{
	size_t	ref_len;

	if (*env_s == NULL)
		return (1);
	ref_len = ft_strlen(ref);
	return (!(ft_strncmp(*env_s, ref, ref_len) == 0 && (*env_s)[ref_len] == '='));
}

static t_bool	is_name(char const *name)
{
	size_t	i;

	if (ft_isalpha(name[0]) != ft_true)
		return (ft_false);
	i = 1;
	while (ft_isalnum(name[i]) == ft_true || name[i] == '_')
		i++;
	return (name[i] == '=');
}

static void	print_env(t_vector *envv)
{
	char const	**env = envv->array;
	size_t		i;

	i = 0;
	while (env[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(env[i++]);
	}
}

int	ms_export(char *argv[], t_vector *env)
{
	size_t	i;
	int		ret;
	char	*str;

	if (argv[1] == NULL)
	{
		print_env(env);
		return (0);
	}
	ret = 0;
	i = 0;
	while (argv[++i])
	{
		if (is_name(argv[i]) == ft_false)
		{
			if (ret == 0)
				ft_err_perror("export: ", ft_err_bad_arg);
			ret = 1;
			continue ;
		}
		ft_vec_remove_all(env, argv[i], (t_destr_func)ft_freederef, (t_cmp_func)str_find);
		str = ft_strdup(argv[i]);
		ft_vec_insert(env, &str, env->size - 1);
	}
	return (ret);
}
