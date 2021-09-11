#include "parser.h"

t_error	dfa_arg(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == ' ')
	{
		parse->dfafunc = dfa_skip_spaces;
		return (error_no_error);
	}
	t->substr.size++;
	if (*str == '"')
		parse->dfafunc = dfa_arg2squotes;
	else if (*str == '\'')
		parse->dfafunc = dfa_arg1squotes;
	else if (*str == '\\')
		parse->dfafunc = dfa_argprotsym;
	return (error_no_error);
}

t_error	dfa_arg1squotes(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	if (*str == '\'')
		parse->dfafunc = dfa_arg;
	return (error_no_error);
}

t_error	dfa_arg2squotes(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	if (*str == '"')
		parse->dfafunc = dfa_arg;
	return (error_no_error);
}

t_error	dfa_argprotsym(char *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	parse->dfafunc = dfa_arg;
	return (error_no_error);
}
