/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_p1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:40:36 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:15:31 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/tokenize.h>
#include <parser/parser.h>

t_ft_err	parse_arg(t_minishell *ms, t_token *token)
{
	t_command		*s_run;

	s_run = ft_vec_back(&ms->node.pipeline);
	if (token->type != e_token_arg)
		return (ft_err_perror("mish: ", ft_err_bad_syntax));
	if (ft_vec_push_back(&s_run->args, &token->substr) != ft_err_ok)
		return (ft_err_perror("mish: ", ft_err_bad_alloc));
	ms->parse_token = (t_itokenfunc)parse_all;
	return (ft_err_ok);
}

t_ft_err	parse_pipe(t_minishell *ms, t_token *token)
{
	t_command		srun;

	(void)token;
	srun_constr(&srun);
	if (ft_vec_push_back(&ms->node.pipeline, &srun) != ft_err_ok)
		return (ft_err_perror("mish: ", ft_err_bad_alloc));
	ms->parse_token = (t_itokenfunc)parse_all;
	return (ft_err_ok);
}

t_ft_err	parse_arg_redir(t_minishell *ms, t_token *token)
{
	t_command		*s_run;
	t_redir			*redir;

	s_run = ft_vec_back(&ms->node.pipeline);
	redir = ft_vec_back(&s_run->redirs);
	if (token->type != e_token_arg)
		return (ft_err_perror("mish: ", ft_err_bad_syntax));
	redir->arg = token->substr;
	ms->parse_token = (t_itokenfunc)parse_all;
	return (ft_err_ok);
}

t_ft_err	parse_redir(t_minishell *ms, t_token *token)
{
	t_command		*srun;
	t_redir			redir;

	srun = ft_vec_back(&ms->node.pipeline);
	redir.fd = -1;
	redir.arg = (t_stringview){NULL, 0};
	redir.type = (t_redir_type)token->type;
	if (ft_vec_push_back(&srun->redirs, &redir) != ft_err_ok)
		return (ft_err_perror("mish: ", ft_err_bad_alloc));
	ms->parse_token = (t_itokenfunc)parse_arg_redir;
	return (ft_err_ok);
}

t_ft_err	parse_commands(t_minishell *ms, t_dfaparse *tokens)
{
	size_t		i;
	t_token		*t;
	t_ft_err	err;

	i = 0;
	while (i < tokens->tokens.size)
	{
		t = ft_vec_at(&tokens->tokens, i);
		err = ms->parse_token(ms, t);
		if (err)
			return (err);
		i++;
	}
	return (err);
}
