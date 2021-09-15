#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <ft_vector.h>

typedef struct s_single_run
{
	// ft_vec_construct(&args, sizeof(char*))
	t_vector	args;
	// ft_vec_construct(&redir_i_stream, sizeof(???))
	t_vector	redir_i_stream;
	// ft_vec_construct(&redir_o_stream, sizeof(???))
	t_vector	redir_o_stream;
}				t_single_run;

inline void	srun_destr(t_single_run *srun)
{
	ft_vec_destructor(&srun->args, free);
	ft_vec_destructor(&srun->redir_i_stream, NULL); // TODO close fd
	ft_vec_destructor(&srun->redir_o_stream, NULL); // TODO close fd
}

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
	// ft_vec_construct(&p_run, sizeof(s_single_run))
	t_vector	p_run;
	// ft_vec_construct(&logic, sizeof(t_cmdlogic))
	t_vector	logic;
}				t_command;

inline void	command_destr(t_command *cmd)
{
	ft_vec_destructor(&cmd->p_run, (t_destrfunc)srun_destr);
	ft_vec_destructor(&cmd->logic, NULL);
}

typedef struct s_minishell
{
	// ft_vec_construct(&logic, sizeof(char*))
	t_vector		env;
	// ft_vec_construct(&logic, sizeof(t_command))
	t_command		cmd;
}				t_minishell;

#endif
