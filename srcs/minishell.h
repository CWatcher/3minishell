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

typedef struct s_single_run
{
	// ft_vec_construct(&args, sizeof(t_stringview))
	t_vector	args;
	// ft_vec_construct(&redir_i_stream, sizeof(t_redir))
	t_vector	redir;
}				t_single_run;

inline void	srun_destr(t_single_run *srun)
{
	ft_vec_destructor(&srun->args, NULL);
	ft_vec_destructor(&srun->redir, NULL);
}

typedef enum
{
	e_logic_arg,
	e_logic_and,
	e_logic_or,
	e_logic_bracket_open,
	e_logic_bracket_close
}			t_logic;

typedef struct s_and_or_node
{
	t_logic		type;
	t_vector	pipeline;
}				t_and_or_node;

inline void	and_or_node_destr(t_and_or_node *node)
{
	ft_vec_destructor(&node->pipeline, (t_destrfunc)srun_destr);
}

typedef struct	s_command
{
	// ft_vec_construct(&p_run, sizeof(t_and_or_node))
	t_vector	and_or_list;
}				t_command;

inline void	command_destr(t_command *cmd)
{
	ft_vec_destructor(&cmd->and_or_list, (t_destrfunc)and_or_node_destr);
}

typedef t_error(	*t_itokenfunc)(void *, void *);

typedef struct s_minishell
{
	// ft_vec_construct(&logic, sizeof(char*))
	t_vector		env;
	// ft_vec_construct(&logic, sizeof(t_and_or_list))
	t_vector		commands;
	t_itokenfunc	parse_token;
}				t_minishell;

t_error	parse(t_minishell *ms, char const *str);
void	null_minishell(t_minishell *ms);

#endif
