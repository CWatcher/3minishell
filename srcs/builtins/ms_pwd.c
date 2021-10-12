/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:43:54 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 04:54:51 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "ft_io.h"

int	ms_pwd(char *argv[], t_vector *env)
{
	char	path[PATH_MAX];

	(void)argv;
	(void)env;
	if (!getcwd(path, PATH_MAX))
		return (ms_perror("pwd", argv[0], NULL, 1));
	ft_putendl_s(path);
	return (0);
}
