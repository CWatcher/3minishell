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

int	main(void)
{
	parse("<< file echo some\\ arg \"ano'ther \"arg; 1||a && b");
	parse("a|b");
	parse("\"ls;\"");
}
