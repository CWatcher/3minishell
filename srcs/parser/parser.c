#include "parser.h"

t_error	dfa_process(char const *str, t_dfaparse *parse)
{
	t_error	err;

	ft_vec_construct(&parse->tokens, sizeof(t_token));
	parse->dfafunc = dfa_skip_spaces;
	while (*str)
	{
		err = parse->dfafunc(str, parse);
		if (err)
			return (err);
		str++;
	}
	if (parse->dfafunc == dfa_arg1squotes || parse->dfafunc == dfa_arg2squotes)
		return (e_dfaerr_parse_unclosed_quote);
}

t_error parse(char const *str)
{
	t_error		err;
	t_dfaparse	dfa;

	err = dfa_process(str, &dfa);
	if (err)
		return (err);
}
