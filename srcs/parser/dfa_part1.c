#include "tokenize.h"

t_ft_err	dfa_create_token(t_dfaparse *parse, t_token token, t_dfafunc func)
{
	if (ft_vec_push_back(&parse->tokens, &token) != ft_err_ok)
		return (ft_err_perror("mish: ", ft_err_bad_alloc));
	parse->dfafunc = func;
	return (ft_err_ok);
}

t_ft_err	dfa_skip_spaces(char const *str, t_dfaparse *parse)
{
	t_stringview const	sv = {(char *)str, 1};

	if (ft_isspace(*str))
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	else if (ft_strchr("<>|&();", *str))
		return (dfa_create_token(parse, (t_token){e_token_logic, sv}, match_operator(*str)));
	else if (*str == '\'')
		return (dfa_create_token(parse, (t_token){e_token_arg, sv}, (t_dfafunc)dfa_arg1quotes));
	else if (*str == '\"')
		return (dfa_create_token(parse, (t_token){e_token_arg, sv}, (t_dfafunc)dfa_arg2quotes));
	else if (*str == '\\')
		return (dfa_create_token(parse, (t_token){e_token_arg, sv}, (t_dfafunc)dfa_argprotsym));
	else
		return (dfa_create_token(parse, (t_token){e_token_arg, sv}, (t_dfafunc)dfa_arg));
	return (ft_err_ok);
}

t_dfafunc	match_operator(char ch)
{
	if (ch == '<')
		return ((t_dfafunc)dfa_op_redir_left);
	if (ch == '>')
		return ((t_dfafunc)dfa_op_redir_right);
	if (ch == '|')
		return ((t_dfafunc)dfa_op_or);
	if (ch == '&')
		return ((t_dfafunc)dfa_op_and);
	if (ch == '(')
		return ((t_dfafunc)dfa_op_brack_left);
	if (ch == ')')
		return ((t_dfafunc)dfa_op_brack_right);
	if (ch == ';')
		return ((t_dfafunc)dfa_op_end);
	return ((t_dfafunc)dfa_skip_spaces);
}
