/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredocarg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:40:11 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:21:33 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <ft_string.h>
#include "open_arg.h"

t_ft_err	open_heredocarg1quotes(t_open_hdarg *oa)
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

t_ft_err	open_heredocarg2quotes(t_open_hdarg *oa)
{
	oa->pos++;
	while (oa->sv.str[oa->pos] != '\"')
	{
		if (ft_vec_push_back(&oa->str_build, &oa->sv.str[(oa->pos)++]) \
						!= ft_err_ok)
			return (ft_err_bad_alloc);
	}
	(oa->pos)++;
	return (ft_err_ok);
}

t_ft_err	real_open_heredocarg(t_open_hdarg *oa)
{
	t_ft_err		err;

	while (oa->pos < oa->sv.size)
	{
		if (oa->sv.str[oa->pos] == '\"')
			err = open_heredocarg2quotes(oa);
		else if (oa->sv.str[oa->pos] == '\'')
			err = open_heredocarg1quotes(oa);
		else
			err = open_heredocargnoquotes(oa);
		if (err != ft_err_ok)
			return (err);
	}
	return (ft_err_ok);
}

char	*open_heredocarg(t_stringview sv)
{
	t_open_hdarg	oa;
	t_ft_err		err;

	oa.pos = 0;
	oa.sv = sv;
	ft_vec_construct(&oa.str_build, sizeof(char));
	ft_vec_reserv(&oa.str_build, sv.size);
	err = real_open_heredocarg(&oa);
	if (err != ft_err_ok)
	{
		ft_err_perror("mish: ", ft_err_bad_alloc);
		ft_vec_destructor(&oa.str_build, NULL);
		return (NULL);
	}
	if (ft_vec_push_back(&oa.str_build, "\0") != ft_err_ok)
	{
		ft_err_perror("mish: ", ft_err_bad_alloc);
		ft_vec_destructor(&oa.str_build, NULL);
		return (NULL);
	}
	return (ft_vec_fetch_array(&oa.str_build, NULL));
}
