#include "tokenize.h"

t_error	dfa_tokenize(char const *str, t_dfaparse *parse)
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
