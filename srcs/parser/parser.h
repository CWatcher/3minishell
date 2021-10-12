/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:41:18 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:16:17 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <ft_string.h>
# include <ft_vector.h>
# include <minishell.h>
# include <parser/tokenize.h>

t_ft_err	parse_all(t_minishell *ms, t_token *token);
t_ft_err	parse_arg(t_minishell *ms, t_token *token);
t_ft_err	parse_pipe(t_minishell *ms, t_token *token);
t_ft_err	parse_arg_redir(t_minishell *ms, t_token *token);
t_ft_err	parse_redir(t_minishell *ms, t_token *token);
t_ft_err	parse_end(t_minishell *ms, t_token *token);
t_ft_err	parse_commands(t_minishell *ms, t_dfaparse *tokens);

#endif
