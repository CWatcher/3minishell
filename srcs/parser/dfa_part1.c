#include "parser.h"

t_error	dfa_create_token(t_dfaparse *parse, t_token token, t_dfafunc func)
{
	if (!ft_vec_push_back(&parse->tokens, &token))
		return (error_allocation_fail);
	parse->dfafunc = func;
	return (error_no_error);
}

t_error	dfa_skip_spaces(char const *str, t_dfaparse *parse)
{
	if (*str == ' ')
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	else if (ft_strchr("<>|&;", *str))
		return (dfa_create_token(parse, (t_token){e_token_logic, {(char *)str, 1}}, (t_dfafunc)dfa_repeat));
	else if (*str == '\'')
		return (dfa_create_token(parse, (t_token){e_token_arg, {(char *)str, 1}}, (t_dfafunc)dfa_arg1quotes));
	else if (*str == '"')
		return (dfa_create_token(parse, (t_token){e_token_arg, {(char *)str, 1}}, (t_dfafunc)dfa_arg2quotes));
	else if (*str == '\\')
		return (dfa_create_token(parse, (t_token){e_token_arg, {(char *)str, 1}}, (t_dfafunc)dfa_argprotsym));
	else
		return (dfa_create_token(parse, (t_token){e_token_arg, {(char *)str, 1}}, (t_dfafunc)dfa_arg));
	return (error_no_error);
}

t_error	dfa_repeat(char const *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == *(t->substr.str))
		t->substr.size++;
	else
		return (dfa_skip_spaces(str, parse));
	return (error_no_error);
}
