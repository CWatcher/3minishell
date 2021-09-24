#include "tokenize.h"

t_ftE	dfa_arg(char const *str, t_dfaparse *parse)
{
	t_token				*t;
	t_stringview const	sv = {(char *)str, 1};

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == ' ')
		return (dfa_skip_spaces(str, parse));
	else if (ft_strchr("<>|&;()", *str))
		return (dfa_create_token(parse, (t_token){e_token_logic, sv}, match_operator(*str)));
	t->substr.size++;
	if (*str == '"')
		parse->dfafunc = (t_dfafunc)dfa_arg2quotes;
	else if (*str == '\'')
		parse->dfafunc = (t_dfafunc)dfa_arg1quotes;
	else if (*str == '\\')
		parse->dfafunc = (t_dfafunc)dfa_argprotsym;
	return (ftE_ok);
}

t_ftE	dfa_arg1quotes(char const *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	if (*str == '\'')
		parse->dfafunc = (t_dfafunc)dfa_arg;
	return (ftE_ok);
}

t_ftE	dfa_arg2quotes(char const *str, t_dfaparse *parse)
{
	t_token *t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	if (*str == '"')
		parse->dfafunc = (t_dfafunc)dfa_arg;
	return (ftE_ok);
}

t_ftE	dfa_argprotsym(char const *str, t_dfaparse *parse)
{
	t_token *t;

	(void)str;
	t = ((t_token *)ft_vec_back(&parse->tokens));
	t->substr.size++;
	parse->dfafunc = (t_dfafunc)dfa_arg;
	return (ftE_ok);
}
