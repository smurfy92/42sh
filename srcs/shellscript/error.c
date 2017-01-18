/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 02:06:06 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 19:04:23 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		error_handler_next(t_script *script)
{
	if (script->errnb == E_INVALID_LOOP)
		ft_putendl_fd("Invalid loop syntax", 2);
	else if (script->errnb == E_WRONG_FILE)
		ft_putendl_fd("Can't open input file", 2);
	else if (script->errnb == E_INVALID_LOOP_FOLDER)
		ft_putendl_fd("Problem opening the folder", 2);
	else if (script->errnb == E_INFINITE_LOOP)
		ft_putendl_fd("Loop seems to be infinite, aborting", 2);
	else
		ft_putendl_fd("Unknown error", 2);
}

void			error_handler(t_script *script)
{
	if (script->errnb == E_TOO_EQU)
		ft_putendl_fd("Too many '=' on a single line, limited to one", 2);
	else if (script->errnb == E_INSTANT)
		ft_putendl_fd("Error during variable assignation", 2);
	else if (script->errnb == E_CONF_TYPES)
		ft_putendl_fd("Conflicting types during assignation", 2);
	else if (script->errnb == E_UNKNOWN_VAR)
		ft_putendl_fd("Unknown variable used", 2);
	else if (script->errnb == E_INCOMPLETE_COND)
		ft_putendl_fd("Invalid condition syntax", 2);
	else if (script->errnb == E_STARTED_COND)
		ft_putendl_fd("Condition hasn't been closed", 2);
	else if (script->errnb == E_MULTI_COMP)
		ft_putendl_fd("Cannot make multiple comparaisons", 2);
	else if (script->errnb == E_INCOMPLETE_COMP)
		ft_putendl_fd("Invalid comparaison", 2);
	else if (script->errnb == E_INVALID_OP)
		ft_putendl_fd("Invalid operation", 2);
	else
		error_handler_next(script);
	free_script(&script);
	ft_exit(get_grp(), 1);
}
