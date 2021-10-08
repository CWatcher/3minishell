#include "tokenize.h"
#include "parser.h"
#include <minishell.h>

t_ft_err	dlrt_dfaparse(t_dfaparse *dfa, t_ft_err err)
{
	ft_vec_destructor(&dfa->tokens, (t_destr_func)NULL);
	return (err);
}

t_ft_err	check_parse(t_minishell *ms)
{
	size_t		i;
	t_command	*scmd;

	i = 0;
	while (i < ms->node.pipeline.size)
	{
		scmd = ft_vec_at(&ms->node.pipeline, i);
		if (scmd->args.size == 0)
			return (ft_err_perror("mish: ", ft_err_bad_syntax));
		i++;
	}
	return (ft_err_ok);
}

t_ft_err	parse(t_minishell *ms, char const *str)
{
	t_dfaparse	tokens;
	t_ft_err		err;

	err = dfa_tokenize(str, &tokens);
	if (err != ft_err_ok)
		return (dlrt_dfaparse(&tokens, err));
	if (tokens.tokens.size == 0)
		return (dlrt_dfaparse(&tokens, ft_err_perror("mish: ", ft_err_bad_syntax)));
	err = parse_commands(ms, &tokens);
	if (err != ft_err_ok)
		return (dlrt_dfaparse(&tokens, err));
	err = check_parse(ms);
	return (dlrt_dfaparse(&tokens, err));
}
