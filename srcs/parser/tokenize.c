#include "tokenize.h"

t_ftE	dfa_tokenize(char const *str, t_dfaparse *parse)
{
	t_ftE	err;

	ft_vec_construct(&parse->tokens, sizeof(t_token));
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	while (*str)
	{
		err = parse->dfafunc(str, parse);
		if (err != ftE_ok)
			return (err);
		str++;
	}
	if (parse->dfafunc == (t_dfafunc)&dfa_arg1quotes \
		|| parse->dfafunc == (t_dfafunc)&dfa_arg2quotes)
		return ((t_ftE)dfaE_parse_unclosed_quote);
	return (ftE_ok);
}
