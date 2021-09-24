#include "tokenize.h"
#include "parser.h"
#include <minishell.h>

t_ftE	dlrt_dfaparse(t_dfaparse *dfa, t_ftE err)
{
	ft_vec_destructor(&dfa->tokens, (t_destrfunc)NULL);
	return (err);
}

t_ftE	parse(t_minishell *ms, char const *str)
{
	t_dfaparse	tokens;
	t_ftE		err;

	err = dfa_tokenize(str, &tokens);
	if (err || tokens.tokens.size == 0)
		return (dlrt_dfaparse(&tokens, err));
	err = parse_commands(ms, &tokens);
	if (err)
		return (dlrt_dfaparse(&tokens, err));
	return (dlrt_dfaparse(&tokens, ftE_ok));
}
