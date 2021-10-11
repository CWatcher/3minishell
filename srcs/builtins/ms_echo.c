/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:43:54 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/11 18:44:49 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_vector.h"
#include "ft_io.h"

int	ms_echo(char *argv[], t_vector *env)
{
	t_bool		newline_on;

	(void)env;
	newline_on = ft_strcmp_s(argv[1], "-n") != 0;
	if (ft_putmultistr_delim(argv + !newline_on + 1, " ") < 0)
		return (1);
	if (newline_on)
		ft_putstr("\n");
	return (0);
}
