#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <ft_vector.h>

typedef enum e_redir_type
{
	e_redir_o_trunc,
	e_redir_o_append,
	e_redir_i_file,
	e_redir_i_stream
}			t_redir_type;

typedef struct s_redir
{
	char			*arg;
	int				fd;
	t_redir_type	type;
}				t_redir;

inline void redir_free(t_redir *redir)
{
	free(redir->arg);
}

typedef struct s_single_run
{
	// ft_vec_construct(&args, sizeof(char*))
	t_vector	args;
	// ft_vec_construct(&redir_i_stream, sizeof(t_redir))
	t_vector	redir;
}				t_single_run;

inline void	srun_destr(t_single_run *srun)
{
	ft_vec_destructor(&srun->args, free);
	ft_vec_destructor(&srun->redir, redir_free);
}

typedef enum {
	e_logic_arg,
	e_logic_and,
	e_logic_or
}			t_logic;

typedef struct s_and_or_node
{
	t_logic		type;
	t_vector	pipeline;
}				t_and_or_node;

inline void	and_or_node_destr(t_and_or_node *node)
{
	ft_vec_destructor(&node->pipeline, srun_destr);
}

typedef struct	s_and_or_list
{
	// ft_vec_construct(&p_run, sizeof(t_and_or_node))
	t_vector	rpn;
}				t_and_or_list;

inline void	and_or_destr(t_and_or_list *cmd)
{
	ft_vec_destructor(&cmd->rpn, (t_destrfunc)and_or_node_destr);
}

typedef struct s_minishell
{
	// ft_vec_construct(&logic, sizeof(char*))
	t_vector		env;
	// ft_vec_construct(&logic, sizeof(t_and_or_list))
	t_and_or_list	and_or_list;
}				t_minishell;

#endif
