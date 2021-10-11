/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:41:22 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:41:23 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_ft_err	dfa_tokenize(char const *str, t_dfaparse *parse)
{
	t_ft_err	err;

	ft_vec_construct(&parse->tokens, sizeof(t_token));
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	while (*str)
	{
		err = parse->dfafunc(str, parse);
		if (err != ft_err_ok)
			return (err);
		str++;
	}
	if (parse->dfafunc == (t_dfafunc)&dfa_arg1quotes \
		|| parse->dfafunc == (t_dfafunc)&dfa_arg2quotes)
		return (ft_err_perror("mish: ", ft_err_unclosedquotes));
	return (ft_err_ok);
}
