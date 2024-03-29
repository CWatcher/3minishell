/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_minihsell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:37:06 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:37:09 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "parser.h"

void	and_or_node_constr(t_and_or_node *node)
{
	ft_vec_construct(&node->pipeline, sizeof(t_command));
}

void	and_or_node_destr(t_and_or_node *node)
{
	ft_vec_destructor(&node->pipeline, (t_destr_func)srun_destr);
}

void	srun_constr(t_command *srun)
{
	ft_vec_construct(&srun->args, sizeof(t_stringview));
	ft_vec_construct(&srun->redirs, sizeof(t_redir));
}

void	srun_destr(t_command *srun)
{
	ft_vec_destructor(&srun->args, NULL);
	ft_vec_destructor(&srun->redirs, NULL);
}

t_ft_err	null_minishell_cmd(t_minishell *ms)
{
	t_command		srun;

	and_or_node_destr(&ms->node);
	srun_constr(&srun);
	and_or_node_constr(&ms->node);
	if (ft_vec_push_back(&ms->node.pipeline, &srun) != ft_err_ok)
		return (ft_err_perror("mish: ", ft_err_bad_alloc));
	ms->parse_token = (t_itokenfunc)parse_all;
	return (ft_err_ok);
}
