#ifndef PARSER_H
# define PARSER_H

# include <ft_string.h>
# include <ft_vector.h>
# include <ft_error.h>

# include "../minishell.h"

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

// ********************
// * OPEN

typedef struct s_single_run
{
	t_vector	args;
	t_vector	redir_in_nfile;
	t_vector	redir_in_afile;
	t_vector	redir_from_file;
	t_vector	redir_from_ins;
}				s_single_run;

typedef struct s_parallel_run
{
	t_vector	pipes;
}				t_parallel_run;

enum e_cmdlogic
{
	e_cmdlogic_bit = (1 << 30),
	e_cmdlogic_and,
	e_cmdlogic_or,
	e_cmdlogic_end,
	e_cmdlogic_bracket_open,
	e_cmdlogic_bracket_close
};

typedef uint64_t t_cmdlogic;

typedef struct s_command
{
	t_vector	p_run;
	t_vector	logic;
}				t_command;

t_error	open_arg(t_minishell *ms, t_stringview sv, char *const *out_str);
t_error	open_argnquotes(t_minishell *ms, t_stringview sv, size_t start, t_vector *out);
t_error	open_arg1quotes(t_minishell *ms, t_stringview sv, size_t start, t_vector *out);
t_error	open_arg2quotes(t_minishell *ms, t_stringview sv, size_t start, t_vector *out);

t_error	parse(t_minishell *ms, char const *str);

#endif
