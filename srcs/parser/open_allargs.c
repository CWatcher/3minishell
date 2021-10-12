/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_allargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 07:07:41 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*clean_exit(t_vector *argv, char **n_argv)
{
	ft_vec_destructor(argv, (t_destr_func)ft_freederef);
	ft_strarr_clear(n_argv);
	return (NULL);
}

char	**open_allargs(t_vector v_stringviews, t_ms_vars const *vars)
{
	const t_stringview	*stringviews = v_stringviews.array;
	char				**n_args;
	t_vector			argv;
	size_t				i;

	ft_vec_construct(&argv, sizeof(char *));
	i = 0;
	while (i < v_stringviews.size)
	{
		n_args = open_arg(stringviews[i], vars);
		if (n_args == NULL)
			return (clean_exit(&argv, n_args));
		if (ft_vec_push_back_n(&argv, n_args, ft_strarr_size(n_args)) \
					!= ft_err_ok)
			return (clean_exit(&argv, n_args));
		free(n_args);
		i++;
	}
	n_args = NULL;
	if (ft_vec_push_back(&argv, &n_args) != ft_err_ok)
		return (clean_exit(&argv, n_args));
	return (ft_vec_fetch_array(&argv, NULL));
}
