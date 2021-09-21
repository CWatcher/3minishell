#include <minishell.h>
#include "parser.h"

void	command_constr(t_command *cmd)
{
	ft_vec_construct(&cmd->and_or_list, sizeof(t_and_or_node));
}

void	command_destr(t_command *cmd)
{
	ft_vec_destructor(&cmd->and_or_list, (t_destrfunc)and_or_node_destr);
}

void	and_or_node_constr(t_and_or_node *node)
{
	ft_vec_construct(&node->pipeline, sizeof(t_single_run));
	node->type = e_logic_arg;
}
void	and_or_node_destr(t_and_or_node *node)
{
	ft_vec_destructor(&node->pipeline, (t_destrfunc)srun_destr);
}

void	srun_constr(t_single_run *srun)
{
	ft_vec_construct(&srun->args, sizeof(t_stringview));
	ft_vec_construct(&srun->redir, sizeof(t_redir));
}

void	srun_destr(t_single_run *srun)
{
	ft_vec_destructor(&srun->args, NULL);
	ft_vec_destructor(&srun->redir, NULL);
}

t_error	null_minishell_cmd(t_minishell *ms)
{
	t_single_run	srun;
	t_and_or_node	and_or_node;
	t_command		cmd;

	ft_vec_clean(&ms->commands, (t_destrfunc)command_destr);
	srun_constr(&srun);
	and_or_node_constr(&and_or_node);
	command_constr(&cmd);
	ft_vec_push_back(&and_or_node.pipeline, &srun);
	ft_vec_push_back(&cmd.and_or_list, &and_or_node);
	ft_vec_push_back(&ms->commands, &cmd);
	ms->parse_token = (t_itokenfunc)parse_all;
	return (error_no_error);
}
