/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:43:54 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 03:10:44 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "ft_vector.h"

int	ms_cd(char *argv[], t_vector *env)
{
	(void)env;
	if (chdir(argv[1]) < 0)
		return (ms_perror("cd", argv[0], NULL, 1));
	return (0);
}
