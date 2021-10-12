/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:38:32 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/12 08:19:26 by fdiego           ###   ########.fr       */
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
#include <ft_exit.h>

void	init_env(t_minishell *ms, char *env[])
{
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_strarr_size(env);
	ft_vec_reserv(&ms->vars.env, size * 1.3);
	i = 0;
	while (i < size)
	{
		str = ft_strdup(env[i]);
		ft_vec_push_back(&ms->vars.env, &str);
		i++;
	}
	str = NULL;
	ft_vec_push_back(&ms->vars.env, &str);
}

void	minishell_init(t_minishell *ms, char *env[])
{
	*ms = (t_minishell){.prompt = PROMPT};
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	using_history();
	ft_vec_construct(&ms->vars.env, sizeof(char *));
	and_or_node_constr(&ms->node);
	init_env(ms, env);
	update_shlvl(&ms->vars.env);
}

void	minishell_destr(t_minishell *ms)
{
	ft_vec_destructor(&ms->vars.env, (t_destr_func)ft_freederef);
	and_or_node_destr(&ms->node);
}

void	minishell_loop(t_minishell *ms)
{
	char		*line;
	t_ft_err	err;

	line = NULL;
	while (ft_true)
	{
		set_sig_handler();
		free(line);
		if (null_minishell_cmd(ms) != ft_err_ok)
			break ;
		line = readline(ms->prompt);
		if (!line)
			break ;
		if (*line == '\0')
			continue ;
		add_history(line);
		err = parse(ms, line);
		if (err == ft_err_bad_syntax || err == ft_err_unclosedquotes)
			ms->vars.status = 258;
		if (err == ft_err_ok)
		{
			set_exesig_handler();
			ms->vars.status = run_pipeline(ms->node.pipeline, &ms->vars);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms;

	(void)argc;
	(void)argv;
	minishell_init(&ms, envp);
	ft_at_exit(&ms, (t_destr_func)minishell_destr);
	minishell_loop(&ms);
	if (isatty(STDIN_FILENO))
		ft_putendl_s("exit");
	ft_exit(ms.vars.status);
}
