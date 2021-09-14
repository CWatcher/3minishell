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
#include "parser/parser.h"

#include <readline/readline.h>

t_error	minishell_construct(t_minishell *ms)
{
	t_ht_construct_args a;

	a.cmpfunc = (t_cmpfunc)ft_strcmp;
	a.hashfunc = (t_hashfunc)ft_hash_str;
	a.key_size = sizeof(char *);
	a.value_size = sizeof(char *);
	ft_ht_construct(&ms->env, a);
	return (error_no_error);
}

int	main(void)
{
}
