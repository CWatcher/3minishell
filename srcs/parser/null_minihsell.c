#include <minishell.h>
#include "parser.h"

void	null_minishell(t_minishell *ms)
{
	t_and_or_node	and_or_node;
	t_command		cmd;

	ft_vec_construct(&cmd.and_or_list, sizeof(t_and_or_node));
	ft_vec_construct(&and_or_node.pipeline, sizeof(t_single_run));
	ft_vec_push_back(&cmd.and_or_list, &and_or_node);
	ft_vec_push_back(&ms->commands, &cmd);
	ms->parse_token = (t_itokenfunc)parse_all;
}