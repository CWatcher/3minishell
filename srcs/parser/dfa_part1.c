#include "parser.h"

t_error	dfa_create_token(t_dfaparse *parse, t_token token, t_dfafunc func)
{
	if (!ft_vec_push_back(&parse->tokens, &token))
		return (error_allocation_fail);
	parse->dfafunc = func;
}

t_error	dfa_skip_spaces(char *str, t_dfaparse *parse)
{
	if (*str == ' ')
		;
	else if (*str == '<')
		return (dfa_create_token(parse, (t_token){e_token_redir, {str, 1}}, dfa_1or2));
	else if (*str == '>')
		return (dfa_create_token(parse, (t_token){e_token_redir, {str, 1}}, dfa_1or2));
	else if (*str == '|' && *(str + 1) != '|')
		return (dfa_create_token(parse, (t_token){e_token_pipe, {str, 1}}, dfa_skip_spaces));
	else if (*str == '|')
		return (dfa_create_token(parse, (t_token){e_token_logic, {str, 1}}, dfa_2));
	else if (*str == '&')
		return (dfa_create_token(parse, (t_token){e_token_logic, {str, 1}}, dfa_2));
	else if (*str == ';')
		return (dfa_create_token(parse, (t_token){e_token_logic, {str, 1}}, dfa_skip_spaces));
	else
		return (dfa_create_token(parse, (t_token){e_token_arg, {str, 1}}, dfa_arg));
	return (error_no_error);
}

t_error	dfa_1or2(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == *(t->substr.str))
		t->substr.size++;
	parse->dfafunc = dfa_skip_spaces;
	return (error_no_error);
}

t_error	dfa_2(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == *(t->substr.str))
		t->substr.size++;
	else
		return (e_dfaerr_parse_unexpected_token);
	parse->dfafunc = dfa_skip_spaces;
	return (error_no_error);
}
