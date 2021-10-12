/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:51:53 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 19:51:54 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <ft_io.h>
#include <ft_string.h>

static void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		ft_putstr("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	ignore(int sig)
{
	(void)sig;
}

void	set_sig_handler(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	set_exesig_handler(void)
{
	signal(SIGINT, ignore);
	signal(SIGQUIT, ignore);
}
