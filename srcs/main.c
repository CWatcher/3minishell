/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:38:32 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/08 19:29:50 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h> // isatty()
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "pipex/pipex.h"
#include "ft_io.h" // ft_get_next_line()

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
}

void	minishell_init(t_minishell *ms, char *env[])
{
	*ms = (t_minishell){.prompt = PROMPT};
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	using_history();
	set_signal_handler();
	ft_vec_construct(&ms->env, sizeof(char *));
	and_or_node_constr(&ms->node);
	init_env(ms, env);
}

void	minishell_destr(t_minishell *ms)
{
	ft_vec_destructor(&ms->env, (t_destrfunc)ft_freederef);
	and_or_node_destr(&ms->node);
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
		line = readline(ms.prompt);
		if (!line)
			break;
		if (isatty(STDIN_FILENO) && *line && ft_strlen(line) > 0)
			add_history(line);
		if (parse(&ms, line) != ftE_ok)
			continue ;
		ms.status = run_pipeline(ms.node.pipeline, ms.env);
	}
	minishell_destr(&ms);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
}
