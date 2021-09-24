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
	t_vector	redir;
}				t_command;

void	srun_constr(t_command *srun);
void	srun_destr(t_command *srun);

typedef enum
{
	e_logic_arg,
	e_logic_andor_bit = 1 << 6,
	e_logic_and = e_logic_andor_bit + 1,
	e_logic_or = e_logic_andor_bit + 2,
	e_logic_bopen_bit = 1 << 7,
	e_logic_bclose_bit = 1 << 8
}			t_logic;

typedef struct s_and_or_node
{
	t_logic		type;
	t_vector	pipeline;
}				t_and_or_node;

void	and_or_node_constr(t_and_or_node *node);
void	and_or_node_destr(t_and_or_node *node);

typedef struct	s_andor_list
{
	// ft_vec_construct(&p_run, sizeof(t_and_or_node))
	t_vector	and_or_list;
}				t_andor_list;

void	command_constr(t_andor_list *cmd);
void	command_destr(t_andor_list *cmd);

typedef t_error(	*t_itokenfunc)(void *, void *);

typedef struct s_minishell
{
	// ft_vec_construct(&logic, sizeof(char*))
	t_vector		env;
	// ft_vec_construct(&logic, sizeof(t_and_or_list))
	t_vector		run_stack;
	t_itokenfunc	parse_token;
}				t_minishell;

char	*open_arg(t_stringview sv, t_vector *env);
t_error	parse(t_minishell *ms, char const *str);
t_error	null_minishell_cmd(t_minishell *ms);
void	set_signal_handler(void);

#endif
