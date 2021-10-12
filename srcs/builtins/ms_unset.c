/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:07:33 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:00:08 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vector.h>
#include <ft_io.h>
#include <ft_string.h>

static int	str_find(char const **env_s, char const *ref)
{
	size_t	ref_len;

	if (*env_s == NULL)
		return (1);
	ref_len = ft_strlen(ref);
	return (!(ft_strncmp(*env_s, ref, ref_len) == 0 \
				&& (*env_s)[ref_len] == '='));
}

static t_bool	is_name(char const *name)
{
	size_t	i;

	if (ft_isalpha(name[0]) == ft_false)
		return (ft_false);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == ft_false && name[i] != '_')
			return (ft_false);
		i++;
	}
	return (ft_true);
}

int	ms_unset(char *argv[], t_vector *env)
{
	size_t	i;
	int		ret;

	if (argv[1] == NULL)
	{
		ft_err_perror("unset: ", ft_err_notenoughargs);
		return (1);
	}
	i = 0;
	ret = 0;
	while (argv[i + 1])
	{
		i++;
		if (is_name(argv[i]) == ft_false)
		{
			if (ret == 0)
				ft_err_perror("unset: ", ft_err_bad_arg);
			ret = 1;
			continue ;
		}
		ft_vec_remove_all(env, argv[i], \
			(t_destr_func)ft_freederef, (t_cmp_func)str_find);
	}
	return (ret);
}
