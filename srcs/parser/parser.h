#ifndef PARSER_H
# define PARSER_H

# include <ft_string.h>
# include <ft_vector.h>
# include <minishell.h>
# include <parser/tokenize.h>

t_ftE	parse_all(t_minishell *ms, t_token *token);
t_ftE	parse_arg(t_minishell *ms, t_token *token);
t_ftE	parse_pipe(t_minishell *ms, t_token *token);
t_ftE	parse_arg_redir(t_minishell *ms, t_token *token);
t_ftE	parse_redir(t_minishell *ms, t_token *token);
t_ftE	parse_end(t_minishell *ms, t_token *token);
t_ftE	parse_commands(t_minishell *ms, t_dfaparse *tokens);

#endif
