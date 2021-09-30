#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <ft_vector.h>
# include <ftdef.h>
# include <ft_string.h>

typedef enum e_redir_type
{
	e_redir_bit = 1 << 7,
	e_redir_o_trunc,
	e_redir_o_append,
	e_redir_i_file,
	e_redir_i_stream
}			t_redir_type;

typedef struct s_redir
{
	t_stringview	arg;
	int				fd;
	t_redir_type	type;
}				t_redir;

typedef struct s_command
{
	// ft_vec_construct(&args, sizeof(t_stringview))
	t_vector	args;
	// ft_vec_construct(&redir_i_stream, sizeof(t_redir))
	t_vector	redirs;
}				t_command;

void	srun_constr(t_command *srun);
void	srun_destr(t_command *srun);

typedef struct s_and_or_node
{
	t_vector	pipeline;
}				t_and_or_node;

void	and_or_node_constr(t_and_or_node *node);
void	and_or_node_destr(t_and_or_node *node);

typedef t_ftE(	*t_itokenfunc)(void *, void *);

typedef struct s_minishell
{
	// ft_vec_construct(&logic, sizeof(char*))
	t_vector		env;
	// ft_vec_construct(&logic, sizeof(t_and_or_list))
	t_and_or_node	node;
	t_itokenfunc	parse_token;
}				t_minishell;

char	*open_arg(t_stringview sv, t_vector *env);
t_ftE	parse(t_minishell *ms, char const *str);
t_ftE	null_minishell_cmd(t_minishell *ms);
void	set_signal_handler(void);

#endif
