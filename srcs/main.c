/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:38:32 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/15 14:43:22 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <bits/sigaction.h>

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

void	debug_print(t_andor_list *andor_list)
{
	for (size_t idx_ao = 0; idx_ao < andor_list->and_or_list.size; idx_ao++)
	{
		t_and_or_node *node = ft_vec_at(&andor_list->and_or_list, idx_ao);
		for (size_t idx_pp = 0; idx_pp < node->pipeline.size; idx_pp++)
		{
			t_command *srun = ft_vec_at(&node->pipeline, idx_pp);
			ft_vec_foreach(&srun->args, (void(*)(void*))print_arg);
			ft_vec_foreach(&srun->redir, (void(*)(void*))print_redir);
		}
	}
}

void	freep(char **p)
{
	free(*p);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;

	(void)argc, (void)argv, (void)env;
	using_history();
	set_signal_handler();
	ft_vec_construct(&ms.env, sizeof(char *));
	ft_vec_construct(&ms.run_stack, sizeof(t_andor_list));
	for (size_t i = 0; env[i]; i++)
	{
		char *str = ft_strdup(env[i]);
		ft_vec_push_back(&ms.env, &str);
	}
	g_env = &ms.env;
	while (t_true)
	{
		null_minishell_cmd(&ms);
		char *line;
		line = readline("> ");
		if (!line)
			break;
		add_history(line);
		parse(&ms, line);
		debug_print(ft_vec_at(&ms.run_stack, 0));
		free(line);
	}
	printf("exit\n");
	ft_vec_destructor(&ms.env, (t_destrfunc)freep);
	ft_vec_destructor(&ms.run_stack, (t_destrfunc)command_destr);
}
