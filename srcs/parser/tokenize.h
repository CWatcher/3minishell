#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <ft_string.h>
# include <ft_vector.h>
# include <ft_error.h>

# include <minishell.h>

// ********************
// * DFA

enum e_token_type
{
	e_token_none,
	e_token_arg,
	e_token_logic,
	e_token_logic_and,
	e_token_logic_or,
	e_token_logic_pipe,
	e_token_logic_background_run,
	e_token_logic_end_command,
	e_token_logic_brack_left,
	e_token_logic_brack_right,
	e_token_logic_redir_o_trunk = e_redir_o_trunc,
	e_token_logic_redir_o_append = e_redir_o_append,
	e_token_logic_redir_i_file = e_redir_i_file,
	e_token_logic_redir_i_stream = e_redir_i_stream,
};

typedef struct s_token
{
	enum e_token_type	type;
	t_stringview		substr;
}				t_token;

typedef t_ft_err(*t_dfafunc)(char const*, void *);

typedef struct s_parse
{
	t_vector	tokens;
	t_dfafunc	dfafunc;
}				t_dfaparse;

t_ft_err	dfa_create_token(t_dfaparse *parse, t_token token, t_dfafunc func);
t_dfafunc	match_operator(char ch);

t_ft_err	dfa_skip_spaces(char const *str, t_dfaparse *parse);

t_ft_err	dfa_repeat(char const *str, t_dfaparse *parse);

t_ft_err	dfa_arg(char const *str, t_dfaparse *parse);
t_ft_err	dfa_arg1quotes(char const *str, t_dfaparse *parse);
t_ft_err	dfa_arg2quotes(char const *str, t_dfaparse *parse);
t_ft_err	dfa_argprotsym(char const *str, t_dfaparse *parse);
t_ft_err	dfa_argskipcurlbraces(char const *str, t_dfaparse *parse);

t_ft_err	dfa_op_brack_left(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_brack_right(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_end(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_or(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_and(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_redir_left(char const *str, t_dfaparse *parse);
t_ft_err	dfa_op_redir_right(char const *str, t_dfaparse *parse);

t_ft_err	dfa_tokenize(char const *str, t_dfaparse *parse);

#endif
