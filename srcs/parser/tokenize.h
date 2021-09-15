#ifndef PARSER_H
# define PARSER_H

# include <ft_string.h>
# include <ft_vector.h>
# include <ft_error.h>

// ********************
// * DFA

enum e_token_type
{
	e_token_none,
	e_token_arg,
	e_token_logic
};

enum e_dfa_error
{
	e_dfaerr_none = error_user_define_error,
	e_dfaerr_parse_unexpected_token,
	e_dfaerr_parse_unclosed_quote
};

typedef struct s_token
{
	enum e_token_type	type;
	t_stringview		substr;
}				t_token;

typedef t_error(*t_dfafunc)(char const*, void *);

typedef struct s_parse
{
	t_vector	tokens;
	t_dfafunc	dfafunc;
}				t_dfaparse;

t_error	dfa_create_token(t_dfaparse *parse, t_token token, t_dfafunc func);

t_error	dfa_skip_spaces(char const *str, t_dfaparse *parse);

t_error	dfa_repeat(char const *str, t_dfaparse *parse);

t_error	dfa_arg(char const *str, t_dfaparse *parse);
t_error	dfa_arg1quotes(char const *str, t_dfaparse *parse);
t_error	dfa_arg2quotes(char const *str, t_dfaparse *parse);
t_error	dfa_argprotsym(char const *str, t_dfaparse *parse);

t_error	dfa_tokenize(char const *str, t_dfaparse *parse);

#endif
