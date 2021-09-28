#include "tokenize.h"
#include "parser.h"
#include <minishell.h>

t_ftE	dlrt_dfaparse(t_dfaparse *dfa, t_ftE err)
{
	ft_vec_destructor(&dfa->tokens, (t_destrfunc)NULL);
	return (err);
}

t_ftE	check_parse(t_minishell *ms)
{
	size_t		i;
	t_command	*scmd;

	i = 0;
	while (i < ms->node.pipeline.size)
	{
		scmd = ft_vec_at(&ms->node.pipeline, i);
		if (scmd->args.size == 0)
			return (ftE_parse_error);
		i++;
	}
	return (ftE_ok);
}

t_ftE	parse(t_minishell *ms, char const *str)
{
	t_dfaparse	tokens;
	t_ftE		err;

	err = dfa_tokenize(str, &tokens);
	if (err != ftE_ok)
		return (dlrt_dfaparse(&tokens, err));
	if (tokens.tokens.size == 0)
		return (dlrt_dfaparse(&tokens, ftE_parse_error));
	err = parse_commands(ms, &tokens);
	if (err != ftE_ok)
		return (dlrt_dfaparse(&tokens, err));
	err = check_parse(ms);
	return (dlrt_dfaparse(&tokens, err));
}
