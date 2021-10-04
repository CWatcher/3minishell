/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:54:21 by CWatcher          #+#    #+#             */
/*   Updated: 2021/10/04 19:46:51 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char**	open_args(t_vector v_stringviews, t_vector env)
{
	const t_stringview	*stringviews = v_stringviews.array;
	size_t				i;
	char				**argv;

	i = 0;
	argv = malloc(sizeof(char *) * (v_stringviews.size + 1));
	if (!argv)
		return (NULL);
	while (i < v_stringviews.size)
	{
		argv[i] = open_arg(stringviews[i], &env);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
