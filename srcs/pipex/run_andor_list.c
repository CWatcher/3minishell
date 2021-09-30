/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_andor_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/29 15:54:21 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../minishell.h"
#include "fork_boost.h"

void	run_pipeline(const t_vector *pipeline, t_vector *env)
{
	size_t				j;
	const t_command		*cmds = pipeline->array;
	const t_stringview	*args;
	pid_t				pid;
	int					status;

	j = 0;
	while (j < pipeline->size)
	{
		args = cmds[j].args.array;
		pid = fork_cmd(args[0].str, env->array, STDIN_FILENO, STDOUT_FILENO);
		waitpid(pid, &status, 0);
		j++;
	}
}

void	run_command_list(t_minishell *ms)
{
	run_pipeline(&ms->node.pipeline, &ms->env);
}
