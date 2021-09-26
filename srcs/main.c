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
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <minishell.h>

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
	g_env = &ms->env;
}

void	minishell_init(t_minishell *ms, char *env[])
{
	using_history();
	set_signal_handler();
	ft_vec_construct(&ms->env, sizeof(char *));
	ft_vec_construct(&ms->run_stack, sizeof(t_andor_list));
	init_env(ms, env);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	ms;
	char		*line;

	(void)argc, (void)argv, (void)env;
	minishell_init(&ms, env);
	line = NULL;
	while (t_true)
	{
		free(line);
		if (null_minishell_cmd(&ms) != ftE_ok)
			break;
		line = readline("> ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		if (parse(&ms, line) != ftE_ok)
			continue ;
		debug_print(ft_vec_at(&ms.run_stack, 0));
	}
	printf("exit\n");
	ft_vec_destructor(&ms.env, (t_destrfunc)freep);
	ft_vec_destructor(&ms.run_stack, (t_destrfunc)command_destr);
}
