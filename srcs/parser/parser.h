#ifndef PARSER_H
# define PARSER_H

# include <ft_string.h>
# include <ft_vector.h>
# include <minishell.h>
# include <parser/tokenize.h>

t_error	parse_all(t_minishell *ms, t_token *token);
t_error	parse_arg(t_minishell *ms, t_token *token);
t_error	parse_pipe(t_minishell *ms, t_token *token);
t_error	parse_arg_redir(t_minishell *ms, t_token *token);
t_error	parse_redir(t_minishell *ms, t_token *token);
t_error	parse_commands(t_minishell *ms, t_dfaparse *tokens);

char	*open_arg(t_stringview sv, t_vector *env);

#endif
