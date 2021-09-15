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
	if (parse->dfafunc == (t_dfafunc)&dfa_arg1squotes || parse->dfafunc == (t_dfafunc)&dfa_arg2squotes)
		return (e_dfaerr_parse_unclosed_quote);
	return (error_no_error);
}

#include <stdio.h>
#include <stdlib.h>
void process(t_token *tk)
{
	char *i = ft_substr(tk->substr.str, 0, tk->substr.size);
	printf("token %i: %s\n", tk->type, i);
	free(i);
}
typedef void(*test)(void*);

t_error parse(char const *str)
{
	t_dfaparse	dfa;
	t_error		err;

	err = dfa_process(str, &dfa);
	if (err)
	{
		ft_vec_destructor(&dfa.tokens, NULL);
		return (err);
	}
	printf("%zu\n", dfa.tokens.size);
	ft_vec_foreach(&dfa.tokens, (test)process);
	ft_vec_destructor(&dfa.tokens, NULL);
	return (error_no_error);
}
