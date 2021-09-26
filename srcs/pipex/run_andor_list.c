#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../minishell.h"
#include "fork_boost.h"

void	run_pipeline(t_vector *pipeline, char *envp[])
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
		pid = fork_cmd(args[0].str, envp, STDIN_FILENO, STDOUT_FILENO);
		waitpid(pid, &status, 0);
		j++;
	}
}

void run_andor_list(t_andor_list *andor_list, char *envp[])
{
	size_t			i;
	t_and_or_node	*andor_node;

	(void)envp;
	i = 0;
	while(i < andor_list->and_or_list.size)
	{
		andor_node = ft_vec_at(&andor_list->and_or_list, i);
		run_pipeline(&andor_node->pipeline, envp);
		i++;
	}
}
