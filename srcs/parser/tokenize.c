#include "tokenize.h"

t_ft_err	dfa_tokenize(char const *str, t_dfaparse *parse)
{
	t_ft_err	err;

	ft_vec_construct(&parse->tokens, sizeof(t_token));
	parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
	while (*str)
	{
		err = parse->dfafunc(str, parse);
		if (err != ft_err_ok)
			return (err);
		str++;
	}
	if (parse->dfafunc == (t_dfafunc)&dfa_arg1quotes \
		|| parse->dfafunc == (t_dfafunc)&dfa_arg2quotes)
		return (ft_err_perror("mish: unclosed quote", \
				(t_ft_err)dfaE_parse_unclosed_quote));
	return (ft_err_ok);
}
