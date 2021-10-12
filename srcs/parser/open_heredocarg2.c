/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredocarg2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 06:52:31 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 06:52:32 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_arg.h"

t_ft_err	open_heredocargnoquotes(t_open_hdarg *oa)
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
		else if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++]) \
					!= ft_err_ok)
			err = ft_err_bad_alloc;
		if (err != ft_err_ok)
			return (err);
	}
	return (ft_err_ok);
}
