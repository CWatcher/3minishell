#include "tokenize.h"
#include "minishell.h"

t_error	dlrt_dfaparse(t_dfaparse *dfa, t_error err)
{
	ft_vec_destructor(dfa, NULL);
	return (err);
}

t_error	parser(t_minishell *ms, char const *str)
{
	t_dfaparse	tokens;
	t_error		err;

	err = dfa_tokenize(str, &tokens);
	if (err)
		return (dlrt_dfaparse(&tokens, err));
	
}
