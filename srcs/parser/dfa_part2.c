#include "tokenize.h"

t_ftE	dfa_op_or(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '|')
	{
		t->type = e_token_logic_or;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ftE_ok);
	}
	else
	{
		t->type = e_token_logic_pipe;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ftE	dfa_op_and(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '&')
	{
		t->type = e_token_logic_and;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ftE_ok);
	}
	else
	{
		t->type = e_token_logic_background_run;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ftE	dfa_op_redir_left(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '<')
	{
		t->type = e_token_logic_redir_i_stream;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ftE_ok);
	}
	else
	{
		t->type = e_token_logic_redir_i_file;
		return (dfa_skip_spaces(str, parse));
	}
}

t_ftE	dfa_op_redir_right(char const *str, t_dfaparse *parse)
{
	t_token	*t;

	t = ((t_token *)ft_vec_back(&parse->tokens));
	if (*str == '>')
	{
		t->type = e_token_logic_redir_o_append;
		t->substr.size++;
		parse->dfafunc = (t_dfafunc)dfa_skip_spaces;
		return (ftE_ok);
	}
	else
	{
		t->type = e_token_logic_redir_o_trunk;
		return (dfa_skip_spaces(str, parse));
	}
}
