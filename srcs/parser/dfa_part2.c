/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfa_part2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:36:48 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:36:49 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_ft_err	dfa_op_or(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '|')
	{
		t->type = e_token_logic_or;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ft_err_ok);
	}
	else
	{
		t->type = e_token_logic_pipe;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ft_err	dfa_op_and(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '&')
	{
		t->type = e_token_logic_and;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ft_err_ok);
	}
	else
	{
		t->type = e_token_logic_background_run;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ft_err	dfa_op_redir_left(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '<')
	{
		t->type = e_token_logic_redir_i_stream;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ft_err_ok);
	}
	else
	{
		t->type = e_token_logic_redir_i_file;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ft_err	dfa_op_redir_right(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '>')
	{
		t->type = e_token_logic_redir_o_append;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ft_err_ok);
	}
	else
	{
		t->type = e_token_logic_redir_o_trunk;
		return (dfa_skip_spaces(str, parse));
	}
}
