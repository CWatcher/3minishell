/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 07:16:22 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:16:23 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ft_err	parse_all(t_minishell *ms, t_token *token)
{
	if (token->type & e_redir_bit)
		return (parse_redir(ms, token));
	if (token->type == e_token_arg)
		return (parse_arg(ms, token));
	if (token->type == e_token_logic_pipe)
		return (parse_pipe(ms, token));
	return (ft_err_perror("mish: ", ft_err_bad_syntax));
}
