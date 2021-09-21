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

#include <readline/readline.h>

void print_string_view(t_stringview *sv)
{
	int size = sv->size;
	printf("%.*s\n", size, sv->str);
}

void print_redir(t_redir *rd)
{
	printf("%i: ", rd->type);
	print_string_view(&rd->arg);
}

void	debug_print(t_command *cmd)
{
	for (size_t idx_ao = 0; idx_ao < cmd->and_or_list.size; idx_ao++)
	{
		t_and_or_node *node = ft_vec_at(&cmd->and_or_list, idx_ao);
		for (size_t idx_pp = 0; idx_pp < node->pipeline.size; idx_pp++)
		{
			t_single_run *srun = ft_vec_at(&node->pipeline, idx_pp);
			ft_vec_foreach(&srun->args, (void(*)(void*))print_string_view);
			ft_vec_foreach(&srun->redir, (void(*)(void*))print_redir);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc, (void)argv, (void)env;
	t_minishell	ms;

	ft_vec_construct(&ms.env, sizeof(char *));
	ft_vec_construct(&ms.commands, sizeof(t_command));
	while (t_true)
	{
		null_minishell_cmd(&ms);
		char *str;
		str = readline("> ");
		parse(&ms, str);
		debug_print(ft_vec_at(&ms.commands, 0));
		free(str);
	}
}
