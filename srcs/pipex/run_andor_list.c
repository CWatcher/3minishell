#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../minishell.h"
#include "fork_boost.h"

void	run_pipeline(const t_vector *pipeline, char *envp[])
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
		pid = fork_cmd(args[0].str, envp, STDIN_FILENO, STDOUT_FILENO);
		waitpid(pid, &status, 0);
		j++;
	}
}

void	run_andor_list(t_andor_list *andor_list, char *envp[])
{
	size_t				i;
	const t_and_or_node	*andor_nodes = andor_list->and_or_list.array;

	(void)envp;
	i = 0;
	while (i < andor_list->and_or_list.size)
	{
		run_pipeline(&andor_nodes[i].pipeline, envp);
		i++;
	}
}
