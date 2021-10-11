/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa_part3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:36:57 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:36:58 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_ft_err	dfa_op_brack_left(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	(void)str;
	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->type = e_token_logic_brack_left;
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	return (ft_err_ok);
}

t_ft_err	dfa_op_brack_right(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	(void)str;
	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->type = e_token_logic_brack_right;
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	return (ft_err_ok);
}

t_ft_err	dfa_op_end(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	(void)str;
	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->type = e_token_logic_end_command;
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	return (ft_err_ok);
}
