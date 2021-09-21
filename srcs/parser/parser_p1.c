#include <parser/tokenize.h>
#include <parser/parser.h>

t_error	parse_all(t_minishell *ms, t_token *token)
{
	if (token->type & e_redir_bit)
		return (parse_redir(ms, token));
	if (token->type == e_token_arg)
		return (parse_arg(ms, token));
	if (token->type == e_token_logic_pipe)
		return (parse_pipe(ms, token));
	if (token->type == e_token_logic_end_command)
		return (parse_end(ms, token));
	return (error_parse_error);
}

t_error	parse_arg(t_minishell *ms, t_token *token)
{
	t_command		*and_or;
	t_and_or_node	*node;
	t_single_run	*s_run;

	and_or = ft_vec_back(&ms->commands);
	node = ft_vec_back(&and_or->and_or_list);
	s_run = ft_vec_back(&node->pipeline);
	if (token->type != e_token_arg)
		return (error_parse_error);
	if (!ft_vec_push_back(&s_run->args, &token->substr))
		return (error_allocation_fail);
	ms->parse_token = (t_itokenfunc)parse_all;
	return (error_no_error);
}

t_error	parse_pipe(t_minishell *ms, t_token *token)
{
	t_command		*and_or;
	t_and_or_node	*node;
	t_single_run	srun;

	(void)token;
	and_or = ft_vec_back(&ms->commands);
	node = ft_vec_back(&and_or->and_or_list);
	srun_constr(&srun);
	if (!ft_vec_push_back(&node->pipeline, &srun))
		return (error_allocation_fail);
	ms->parse_token = (t_itokenfunc)parse_all;
	return (error_no_error);
}

t_error	parse_arg_redir(t_minishell *ms, t_token *token)
{
	t_command		*and_or;
	t_and_or_node	*node;
	t_single_run	*s_run;
	t_redir			*redir;

	and_or = ft_vec_back(&ms->commands);
	node = ft_vec_back(&and_or->and_or_list);
	s_run = ft_vec_back(&node->pipeline);
	redir = ft_vec_back(&s_run->redir);
	if (token->type != e_token_arg)
		return (error_parse_error);
	redir->arg = token->substr;
	ms->parse_token = (t_itokenfunc)parse_all;
	return (error_no_error);
}

t_error parse_end(t_minishell *ms, t_token *token)
{
	t_single_run	srun;
	t_and_or_node	and_or_node;
	t_command		cmd;

	(void)token;
	srun_constr(&srun);
	and_or_node_constr(&and_or_node);
	command_constr(&cmd);
	if (!ft_vec_push_back(&and_or_node.pipeline, &srun))
		return (error_allocation_fail);
	if (!ft_vec_push_back(&cmd.and_or_list, &and_or_node))
		return (error_allocation_fail);
	if (!ft_vec_push_back(&ms->commands, &cmd))
		return (error_allocation_fail);
	ms->parse_token = (t_itokenfunc)parse_all;
	return (error_no_error);
}

t_error	parse_redir(t_minishell *ms, t_token *token)
{
	t_command		*and_or;
	t_and_or_node	*node;
	t_single_run	*srun;
	t_redir			redir;

	and_or = ft_vec_back(&ms->commands);
	node = ft_vec_back(&and_or->and_or_list);
	srun = ft_vec_back(&node->pipeline);
	redir.fd = -1;
	redir.arg = (t_stringview){NULL, 0};
	redir.type = (t_redir_type)token->type;
	if (!ft_vec_push_back(&srun->redir, &redir))
		return (error_allocation_fail);
	ms->parse_token = (t_itokenfunc)parse_arg_redir;
	return (error_no_error);
}

t_error	parse_commands(t_minishell *ms, t_dfaparse *tokens)
{
	size_t	i;
	t_token	*t;
	t_error	err;

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
