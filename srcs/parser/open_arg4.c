/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 07:16:34 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:16:35 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_arg.h"

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
		else if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++]) \
						!= ft_err_ok)
			return (ft_err_bad_alloc);
		if (err)
			return (err);
	}
	(oa->pos)++;
	return (ft_err_ok);
}
