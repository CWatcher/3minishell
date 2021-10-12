/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_arg.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiego <fdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 06:59:11 by fdiego            #+#    #+#             */
/*   Updated: 2021/10/12 07:15:09 by fdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_ARG_H
# define OPEN_ARG_H

# include <ft_vector.h>
# include <ft_string.h>
# include "../minishell.h"

typedef struct s_open_arg {
	t_vector		arg_build;
	t_vector		str_build;
	t_stringview	sv;
	size_t			pos;
}			t_open_arg;

t_ft_err	push_env_to_args_spaces(t_open_arg *oa, char *env_v, size_t *pos);
t_ft_err	push_env_to_args(t_open_arg *oa, char *env_v);
t_ft_err	open_arg_env(t_open_arg *oa, const t_ms_vars *vars);
t_ft_err	open_arg_env_quotes(t_open_arg *oa, const t_ms_vars *vars);
t_ft_err	open_argnoquotes(t_open_arg *oa, const t_ms_vars *vars);
char		*env_value(t_stringview key, const t_ms_vars *vars);
t_ft_err	choose_name_brack(t_open_arg *oa, t_stringview *name);
t_ft_err	choose_name_nobrack(t_open_arg *oa, t_stringview *name);
t_ft_err	choose_name(t_open_arg *oa, t_stringview *name);
t_ft_err	open_arg1quotes(t_open_arg *oa);
t_ft_err	open_arg2quotes(t_open_arg *oa, const t_ms_vars *vars);

typedef struct s_open_hdarg {
	t_vector		str_build;
	t_stringview	sv;
	size_t			pos;
}			t_open_hdarg;

t_ft_err	open_heredocargnoquotes(t_open_hdarg *oa);

#endif
