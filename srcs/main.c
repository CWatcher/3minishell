/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:38:32 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/03 20:15:48 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "pipex/pipex.h"

t_vector	*g_env;

void print_arg(t_stringview *sv)
{
	char *arg = open_arg(*sv, g_env);
	if (arg)
		printf("%s\n", arg);
	else
		printf("(null)\n");
	free(arg);
}

void print_redir(t_redir *rd)
{
	printf("%i: ", rd->type);
	print_arg(&rd->arg);
}

void	debug_print(t_and_or_node *node)
{
	for (size_t idx_pp = 0; idx_pp < node->pipeline.size; idx_pp++)
	{
		t_command *srun = ft_vec_at(&node->pipeline, idx_pp);
		ft_vec_foreach(&srun->args, (void(*)(void*))print_arg);
		ft_vec_foreach(&srun->redirs, (void(*)(void*))print_redir);
	}
}

void	freep(char **p)
{
	free(*p);
}

void	init_env(t_minishell *ms, char *env[])
{
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_strarr_size(env);
	ft_vec_reserv(&ms->env, size * 1.3);
	i = 0;
	while (i < size)
	{
		str = ft_strdup(env[i]);
		ft_vec_push_back(&ms->env, &str);
		i++;
	}
	str = NULL;
	ft_vec_push_back(&ms->env, &str);
	g_env = &ms->env;
}

void	minishell_init(t_minishell *ms, char *env[])
{
	using_history();
	set_signal_handler();
	ft_vec_construct(&ms->env, sizeof(char *));
	and_or_node_constr(&ms->node);
	init_env(ms, env);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;
	char		*line;

	(void)argc;
	(void)argv;
	minishell_init(&ms, envp);
	line = NULL;
	while (t_true)
	{
		free(line);
		if (null_minishell_cmd(&ms) != ftE_ok)
			break;
		line = readline(PROMPT);
		if (!line)
			break;
		if (*line)
			add_history(line);
		if (parse(&ms, line) != ftE_ok)
			continue ;
		debug_print(&ms.node);
		ms.status = run_pipeline(ms.node.pipeline, ms.env);
	}
	printf("exit\n");
	ft_vec_destructor(&ms.env, (t_destrfunc)freep);
	and_or_node_destr(&ms.node);
}
