#include "tokenize.h"
#include "parser.h"
#include <minishell.h>

t_error	dlrt_dfaparse(t_dfaparse *dfa, t_error err)
{
	ft_vec_destructor(&dfa->tokens, (t_destrfunc)NULL);
	return (err);
}

typedef	t_error(*t_tokenparsefunc)(t_minishell*, t_token *);

t_error	parse(t_minishell *ms, char const *str)
{
	t_dfaparse	tokens;
	t_error		err;

	err = dfa_tokenize(str, &tokens);
	if (err || tokens.tokens.size == 0)
		return (dlrt_dfaparse(&tokens, err));
	parse_commands(ms, &tokens);
	return (error_no_error);
}
