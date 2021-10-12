/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:40:17 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:14:33 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "open_arg.h"

t_ft_err	real_open_arg(t_open_arg *oa, const t_ms_vars *vars)
{
	t_ft_err		err;

	while (oa->pos < oa->sv.size)
	{
		if (oa->sv.str[oa->pos] == '\"')
			err = open_arg2quotes(oa, vars);
		else if (oa->sv.str[oa->pos] == '\'')
			err = open_arg1quotes(oa);
		else
			err = open_argnoquotes(oa, vars);
		if (err != ft_err_ok)
			return (err);
	}
	return (ft_err_ok);
}

static void	*clean_open_arg(t_open_arg *oa, t_ft_err err)
{
	ft_err_perror("mish: ", err);
	ft_vec_destructor(&oa->str_build, NULL);
	ft_vec_destructor(&oa->arg_build, (t_destr_func)ft_freederef);
	return (NULL);
}

void	open_arg_constr(t_open_arg *oa, t_stringview sv)
{
	oa->pos = 0;
	oa->sv = sv;
	ft_vec_construct(&oa->str_build, sizeof(char));
	ft_vec_reserv(&oa->str_build, sv.size);
	ft_vec_construct(&oa->arg_build, sizeof(char *));
}

char	**open_arg(t_stringview sv, const t_ms_vars *vars)
{
	t_open_arg		oa;
	t_ft_err		err;
	char			*str;

	open_arg_constr(&oa, sv);
	err = real_open_arg(&oa, vars);
	if (err != ft_err_ok)
		return (clean_open_arg(&oa, err));
	err = ft_err_ok;
	if (oa.str_build.size != 0 || oa.arg_build.size == 0)
	{
		ft_vec_push_back(&oa.str_build, "\0");
		str = ft_vec_fetch_array(&oa.str_build, NULL);
		err = ft_vec_push_back(&oa.arg_build, &str);
		if (err != ft_err_ok)
			free(str);
	}
	str = NULL;
	err |= ft_vec_push_back(&oa.arg_build, &str);
	if (err != ft_err_ok)
		return (clean_open_arg(&oa, ft_err_bad_alloc));
	return (ft_vec_fetch_array(&oa.arg_build, NULL));
}
