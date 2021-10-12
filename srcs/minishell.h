/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:51:35 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 06:18:54 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <ft_vector.h>
# include <ftdef.h>
# include <ft_string.h>

# define PROMPT "mish-0.6$ "
# define C_BUILTINS 1

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
	t_vector	args;
	t_vector	redirs;
}				t_command;

void			srun_constr(t_command *srun);
void			srun_destr(t_command *srun);

typedef struct s_and_or_node
{
	t_vector	pipeline;
}				t_and_or_node;

void			and_or_node_constr(t_and_or_node *node);
void			and_or_node_destr(t_and_or_node *node);

typedef t_ft_err(	*t_itokenfunc)(void *, void *);
typedef int(		*t_builtin_func)(char *argv[], t_vector *env);

typedef struct s_builtin_entry
{
	const char		*name;
	t_builtin_func	func;
}	t_builtin_entry;

typedef struct s_ms_vars
{
	int				status;
	t_vector		env;
}				t_ms_vars;

typedef struct s_minishell
{
	t_ms_vars		vars;
	t_and_or_node	node;
	t_itokenfunc	parse_token;
	char			*prompt;
}				t_minishell;

char			**open_arg(t_stringview sv, const t_ms_vars *vars);
char			*open_heredocarg(t_stringview sv);
char			**open_allargs(t_vector v_stringviews, const t_ms_vars *vars);
t_bool			open_redirs(t_vector v_redirs, const t_ms_vars *vars,
					int *p_fd_in, int *p_fd_out);
t_ft_err		parse(t_minishell *ms, char const *str);
t_ft_err		null_minishell_cmd(t_minishell *ms);
void			minishell_destr(t_minishell *ms);
void			set_sig_handler(void);
void			set_exesig_handler(void);
t_builtin_func	find_builtin(const char *s);
int				ms_echo(char *argv[], t_vector *env);
int				ms_exit(char *argv[], t_vector *env);
int				ms_export(char *argv[], t_vector *env);
int				ms_unset(char *argv[], t_vector *env);
int				ms_env(char *argv[], t_vector *env);
int				ms_pwd(char *argv[], t_vector *env);
int				ms_cd(char *argv[], t_vector *env);
int				ms_perror(const char *cmd, const char *arg,
					const char *msg, int ret);

#endif
