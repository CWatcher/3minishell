#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../minishell.h"
#include "fork_boost.h"

void	run_pipeline(t_vector *pipeline, t_vector *envp)
{
	size_t		j;
	t_command	*cmd;
	pid_t		pid;
	int			status;

	j = 0;
	while (j < pipeline->size)
	{
		cmd = ft_vec_at(pipeline, j);
		t_stringview *args = cmd->args.array;
		pid = fork_cmd(args[0].str, envp->array, STDIN_FILENO, STDOUT_FILENO);
		waitpid(pid, &status, 0);
		j++;
	}
}

void run_command_list(t_minishell *ms)
{
	run_pipeline(&ms->node.pipeline, &ms->env);
}
