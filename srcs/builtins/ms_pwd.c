/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:43:54 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 08:55:13 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "ft_io.h"

int	ms_pwd(char *argv[], t_vector *env)
{
	t_vector	path;

	(void)argv;
	(void)env;
	ft_vec_construct(&path, sizeof(char));
	ft_vec_reserv(&path, 256);
	while (!getcwd(path.array, path.capacity))
	{
		if (path.capacity * 2 > 524288)
		{
			ft_vec_destructor(&path, NULL);
			return (ms_perror("pwd", argv[0], "path too long", 1));
		}
		if (ft_vec_reserv(&path, path.capacity * 2) != ft_err_ok)
		{
			ft_vec_destructor(&path, NULL);
			return (ms_perror("pwd", argv[0], "allocation error", 1));
		}
	}
	ft_putendl_s(path.array);
	ft_vec_destructor(&path, NULL);
	return (0);
}
