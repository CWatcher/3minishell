/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_allargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/11 19:39:22 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! \todo allocation handle
char**	open_allargs(t_vector v_stringviews, t_vector env)
{
	const t_stringview	*stringviews = v_stringviews.array;
	size_t				i;
	char				**n_args;
	t_vector			argv;

	ft_vec_construct(&argv, sizeof(char*));
	i = 0;
	while (i < v_stringviews.size)
	{
		n_args = open_arg(stringviews[i], &env);
		if (n_args == NULL)
		{
			ft_vec_destructor(&argv, (t_destr_func)ft_freederef);
			return (NULL);
		}
		ft_vec_push_back_n(&argv, n_args, ft_strarr_size(n_args));
		free(n_args);
		i++;
	}
	n_args = NULL;
	ft_vec_push_back(&argv, &n_args);
	return (ft_vec_fetch_array(&argv, NULL));
}
