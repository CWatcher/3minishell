#include "parser.h"

t_error	dfa_process(char const *str, t_dfaparse *parse)
{
	t_error	err;

	ft_vec_construct(&parse->tokens, sizeof(t_token));
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	while (*str)
	{
		err = parse->dfafunc(str, parse);
		if (err)
			return (err);
		str++;
	}
	if (parse->dfafunc == (t_dfafunc)&dfa_arg1quotes \
		|| parse->dfafunc == (t_dfafunc)&dfa_arg2quotes)
		return (e_dfaerr_parse_unclosed_quote);
	return (error_no_error);
}

t_error parse(t_minishell *ms, char const *str)
{
	t_dfaparse	dfa;
	t_error		err;

	(void)ms;
	err = dfa_process(str, &dfa);
	if (err)
	{
		ft_vec_destructor(&dfa.tokens, NULL);
		return (err);
	}
	return (error_no_error);
}
