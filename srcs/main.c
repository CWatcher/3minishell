/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:38:32 by CWatcher          #+#    #+#             */
/*   Updated: 2021/09/08 20:03:41 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <minishell.h>
#include <readline/readline.h>

#include <readline/readline.h>

int	main(int argc, char *argv[], char *env[])
{
	(void)argc, (void)argv, (void)env;
	t_minishell	ms;

	ft_vec_construct(&ms.env, sizeof(char *));
	ft_vec_construct(&ms.commands, sizeof(t_command));
	while (t_true)
	{
		char *str;
		str = readline("> ");
		parse(&ms, str);
	}
}
